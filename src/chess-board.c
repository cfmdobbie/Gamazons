/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 8; tab-width: 8 -*- */
/* board.c
 *
 * Copyright (C) 2001  JP Rosevear
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * Author: JP Rosevear
 */

#include <gdk-pixbuf/gnome-canvas-pixbuf.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

#include "makros.h"
#include "prefs.h"
#include "board.h"

struct _BoardPrivate {
   double orig_x;
   double orig_y;
   double curr_x;
   double curr_y;
   Square from;
   Square to;
   Square selected_from;
   GnomeCanvasItem *selected;

   guint light_rgba;
   guint dark_rgba;

   guint size;
   guint piece_size;

   Position *pos;
   gboolean flip;

   char db[120];
   GnomeCanvasItem *db_image[120];
   GnomeCanvasItem *squares[100];
};

/* Class signals */
enum {
   MOVE_SIGNAL,
   FLIP_SIGNAL,
   LAST_SIGNAL
};
static gint board_signals[LAST_SIGNAL] = { 0 };

enum {
   ARG_0,
   ARG_LIGHT_COLOR_RGBA,
   ARG_DARK_COLOR_RGBA,
};

/* Prototypes */
static void class_init (BoardClass *klass);
static void init (Board *board);
static void set_arg (GtkObject *object, GtkArg *arg, guint arg_id);
static void get_arg (GtkObject *object, GtkArg *arg, guint arg_id);
static void size_allocate (GtkWidget *widget, GtkAllocation *allocation);
static void destroy (GtkObject *obj);

static void board_draw (Board *board);
static void board_update (Board *board);

static GnomeCanvasClass *parent_class = NULL;

    GtkType
board_get_type (void)
{
   static GtkType type = 0;

   if (type == 0)
     {
      static const GtkTypeInfo info =
       	{
	 "Board",
	 sizeof (Board),
	 sizeof (BoardClass),
	 (GtkClassInitFunc) class_init,
	 (GtkObjectInitFunc) init,
	 /* reserved_1 */ NULL,
	 /* reserved_2 */ NULL,
	 (GtkClassInitFunc) NULL,
       	};

      type = gtk_type_unique (gnome_canvas_get_type (), &info);
     }

   return type;
}

    static void
class_init (BoardClass *klass)
{
   GtkObjectClass *object_class;
   GtkWidgetClass *widget_class;

   object_class = GTK_OBJECT_CLASS (klass);
   widget_class = GTK_WIDGET_CLASS (klass);

   parent_class = gtk_type_class (gnome_canvas_get_type ());

   board_signals[MOVE_SIGNAL]
       = gtk_signal_new ("move",
	       GTK_RUN_FIRST,
	       object_class->type,
	       GTK_SIGNAL_OFFSET (BoardClass, move),
	       gtk_marshal_NONE__INT_INT,
	       GTK_TYPE_NONE, 2,
	       GTK_TYPE_INT, GTK_TYPE_INT);

   board_signals[FLIP_SIGNAL]
       = gtk_signal_new ("flip",
	       GTK_RUN_FIRST,
	       object_class->type,
	       GTK_SIGNAL_OFFSET (BoardClass, flip),
	       gtk_marshal_NONE__BOOL,
	       GTK_TYPE_NONE, 1,
	       GTK_TYPE_BOOL);

   gtk_object_class_add_signals (object_class,
	   board_signals,
	   LAST_SIGNAL);

   gtk_object_add_arg_type ("Board::light_color_rgba",
	   GTK_TYPE_UINT,
	   GTK_ARG_READWRITE,
	   ARG_LIGHT_COLOR_RGBA);
   gtk_object_add_arg_type ("Board::dark_color_rgba",
	   GTK_TYPE_UINT,
	   GTK_ARG_READWRITE,
	   ARG_DARK_COLOR_RGBA);

   object_class->set_arg = set_arg;
   object_class->get_arg = get_arg;
   object_class->destroy = destroy;
   widget_class->size_allocate = size_allocate;

   klass->move = NULL;
}


    static void
init (Board *board)
{
   BoardPrivate *priv;
   int i;

   priv = g_new0 (BoardPrivate, 1);

   board->priv = priv;

   priv->light_rgba = GNOME_CANVAS_COLOR (144, 238, 144);
   priv->dark_rgba = GNOME_CANVAS_COLOR (0, 100, 0);

   priv->flip = FALSE;
   for (i = 0; i < 120; i++)
      priv->db[i] = -1;
   for (i = 0; i < 120; i++)
      priv->db_image[i] = NULL;

   priv->pos = POSITION (position_new_initial ());

   priv->size = PIECE_SIZE * 8;
   priv->piece_size = PIECE_SIZE;

   gtk_widget_set_usize (GTK_WIDGET (board), priv->size, priv->size);

   board_draw (board);
   board_update (board);

   gnome_canvas_set_pixels_per_unit (GNOME_CANVAS (board), PIECE_SIZE);
}



    static void
set_arg (GtkObject *object, GtkArg *arg, guint arg_id)
{
   switch (arg_id) {
       case ARG_LIGHT_COLOR_RGBA:
	   board_set_light_color (BOARD (object), GTK_VALUE_UINT (*arg));
	   break;
       case ARG_DARK_COLOR_RGBA:
	   board_set_dark_color (BOARD (object), GTK_VALUE_UINT (*arg));
	   break;
   }
}

    static void
get_arg (GtkObject *object, GtkArg *arg, guint arg_id)
{
   switch (arg_id) {
       case ARG_LIGHT_COLOR_RGBA:
	   GTK_VALUE_UINT (*arg) = board_get_light_color (BOARD (object));
	   break;
       case ARG_DARK_COLOR_RGBA:
	   GTK_VALUE_UINT (*arg) = board_get_dark_color (BOARD (object));
	   break;
   }
}

    static void
size_allocate (GtkWidget *widget, GtkAllocation *allocation)
{
   Board *board;
   BoardPrivate *priv;

   board = BOARD (widget);
   priv = board->priv;

   (*GTK_WIDGET_CLASS (parent_class)->size_allocate) (widget, allocation);

   priv->size = MIN (allocation->width, allocation->height);
   priv->piece_size = priv->size / 8;

   gnome_canvas_set_pixels_per_unit (GNOME_CANVAS (board), priv->size / 8);
   gnome_canvas_scroll_to (GNOME_CANVAS (board), 0, 0);
}

    GtkWidget *
board_new () 
{
   GtkWidget *w;

   gtk_widget_push_visual (gdk_rgb_get_visual ());
   gtk_widget_push_colormap (gdk_rgb_get_cmap ());

   w = GTK_WIDGET (gtk_type_new (TYPE_BOARD));

   gtk_widget_pop_colormap ();
   gtk_widget_pop_visual ();

   return w;
}

    Position *
board_get_position (Board *board) 
{
   BoardPrivate *priv;

   priv = board->priv;

   return priv->pos;
}

    void 
board_set_position (Board *board, Position *pos) 
{
   BoardPrivate *priv;
   Position     *old_pos;

   priv = board->priv;

   old_pos = priv->pos;
   priv->pos = position_copy (pos);
   gtk_object_unref (GTK_OBJECT (old_pos));

   board_update (board);
}

    static void
set_colors (Board *board) 
{
   BoardPrivate *priv;
   int i, j;

   priv = board->priv;

   for (i = 0; i < 8; i++)
      for (j = 0; j < 8; j++)
	 gnome_canvas_item_set (priv->squares[i * 8 +j],
		 "fill_color_rgba", 
		 ((i + j) % 2) ? priv->dark_rgba 
		 : priv->light_rgba,
		 NULL);
}

    guint32 
board_get_light_color (Board *board)
{
   BoardPrivate *priv;

   priv = board->priv;

   return priv->light_rgba;
}

    void 
board_set_light_color (Board *board, guint32 rgba)
{
   BoardPrivate *priv;

   priv = board->priv;

   priv->light_rgba = rgba;

   set_colors (board);

   gtk_widget_queue_draw (GTK_WIDGET (board));
}

    guint32 
board_get_dark_color (Board *board)
{
   BoardPrivate *priv;

   priv = board->priv;

   return priv->dark_rgba;
}

    void 
board_set_dark_color (Board *board, guint32 rgba)
{
   BoardPrivate *priv;

   priv = board->priv;

   priv->dark_rgba = rgba;

   set_colors (board);

   gtk_widget_queue_draw (GTK_WIDGET (board));
}

    void 
board_set_flip (Board *board, gboolean flipped) 
{
   BoardPrivate *priv;

   priv = board->priv;

   priv->flip = flipped;

   gtk_signal_emit (GTK_OBJECT (board),
	   board_signals[FLIP_SIGNAL],
	   priv->flip);
}

    void 
board_flip (Board *board) 
{
   BoardPrivate *priv;

   priv = board->priv;

   if (priv->flip)
      priv->flip = FALSE;
   else
      priv->flip = TRUE;

   gtk_signal_emit (GTK_OBJECT (board),
	   board_signals[FLIP_SIGNAL],
	   priv->flip);
}

    void
board_move (Board *board, Square from, Square to)
{
   BoardPrivate *priv;

   priv = board->priv;

   position_move (priv->pos, from, to);
   board_update (board);
}

    static int
get_square (double x, double y, gboolean flip)
{
   Square from;

   if (!flip)
      from = A1 + (Square)x  + 10 * (7 - (Square)y);
   else
      from = H8 - (Square)x - 10 * (7 - (Square)y);

   return from;
}

    static void
mark_square (GnomeCanvasItem *square)
{
   gnome_canvas_item_set (square, "outline_color", "red", NULL);
}

    static void
clear_square (GnomeCanvasItem **square)
{
   gnome_canvas_item_set (*square, "outline_color", NULL, NULL);
   *square = NULL;
}

    static void
try_move (Board *board, GnomeCanvasItem *item)
{
   BoardPrivate *priv;

   priv = board->priv;

   priv->to = position_move_normalize (priv->pos, priv->from, priv->to);
   if (priv->to) {
      position_move (priv->pos, priv->from, priv->to);
      board_update (board);
      gtk_signal_emit (GTK_OBJECT (board),
	      board_signals [MOVE_SIGNAL],
	      priv->from,
	      priv->to);
   } else if (item != NULL) {
      gnome_canvas_item_move (item,
	      priv->orig_x - priv->curr_x,
	      priv->orig_y - priv->curr_y);
   }
}

    static int
board_press_cb (GnomeCanvasItem *item, GdkEvent *event, gpointer data)
{
   Board *board;
   BoardPrivate *priv;
   double drop_x, drop_y;
   double new_x, new_y;

   board = BOARD (item->canvas);
   priv = board->priv;

   if (data) {
      item = priv->db_image [GPOINTER_TO_INT (data)];
      if (item == NULL && event->type != GDK_BUTTON_RELEASE) 
	 return 0;
   }

   switch (event->type) {
       case GDK_BUTTON_PRESS:
	   if (event->button.button != 1)
	      break;	

	   priv->orig_x = priv->curr_x = event->button.x;
	   priv->orig_y = priv->curr_y = event->button.y;
	   gnome_canvas_item_raise_to_top (item);
	   gnome_canvas_item_grab (item,
		   GDK_POINTER_MOTION_MASK | 
		   GDK_BUTTON_RELEASE_MASK,
		   NULL,
		   event->button.time);

	   priv->from = get_square (priv->curr_x,
		   priv->curr_y,
		   priv->flip);
	   priv->to = priv->from;
	   break;

       case GDK_MOTION_NOTIFY:
	   if ((event->motion.state & GDK_BUTTON1_MASK)) {
	      new_x = event->motion.x;
	      new_y = event->motion.y;
	      gnome_canvas_item_move (item, 
		      new_x - priv->curr_x,
		      new_y - priv->curr_y);

	      if (priv->selected != NULL)
		 clear_square (&priv->selected);

	      priv->curr_x = new_x;
	      priv->curr_y = new_y;
	   }
	   break;

       case GDK_BUTTON_RELEASE:
	   if (event->button.button != 1)
	      break;

	   if (item != NULL)
	      gnome_canvas_item_ungrab (item, event->button.time);

	   drop_x = event->button.x;
	   drop_y = event->button.y;

	   priv->to = get_square (drop_x, drop_y, priv->flip);
	   if (priv->to == priv->from && priv->selected == NULL) {
	      priv->selected = priv->squares [(int)drop_x * 8 + (int)drop_y];

	      mark_square (priv->selected);
	      gnome_canvas_item_move (item, 
		      priv->orig_x - priv->curr_x,
		      priv->orig_y - priv->curr_y);
	      priv->selected_from = priv->from;
	      break;
	   } else if (priv->to == priv->from) {
	      priv->from = priv->selected_from;
	   }

	   try_move (board, item);
	   if (priv->selected)
	      clear_square (&priv->selected);
	   break;
       default:
   }

   return 0;
}

    static GnomeCanvasItem *
board_draw_piece (Board *board, Square sq, Piece piece)
{
   BoardPrivate *priv;
   GdkPixbuf *pb = NULL;
   GnomeCanvasItem *image;
   GnomeCanvasGroup *root;
   double x, y, w, h;
   char *fname, *s = NULL;

   int i,j;

   root = GNOME_CANVAS_GROUP (gnome_canvas_root (GNOME_CANVAS (board)));
   priv = board->priv;

   i= 9 - sq / 10 ;
   j= sq % 10 - 1;

   x = j;
   y = i;

   switch (piece)  {
       case EMPTY:  return NULL; break;
       case WP  :  s = "P.png";  break;
       case WN  :  s = "N.png";  break;
       case WB  :  s = "B.png";  break;
       case WR  :  s = "R.png";  break;
       case WQ  :  s = "Q.png";  break;
       case WK  :  s = "K.png";  break;
       case BP  :  s = "p.png";  break;
       case BN  :  s = "n.png";  break;
       case BB  :  s = "b.png";  break;
       case BR  :  s = "r.png";  break;
       case BQ  :  s = "q.png";  break;
       case BK  :  s = "k.png";  break;
       default  :  g_assert_not_reached ();
   }

   fname = g_strconcat (prefs_get_piecedir (), s, NULL);
   pb = gdk_pixbuf_new_from_file (fname);
   g_free (fname);

   /* If not installed */
   if (pb == NULL) {
      fname = g_strconcat ("../Sets/", s, NULL);
      pb = gdk_pixbuf_new_from_file (fname);
      g_free (fname);
   }  
   g_assert (pb != NULL);

   w = gdk_pixbuf_get_width (pb);
   h = gdk_pixbuf_get_height (pb);

   image = gnome_canvas_item_new (root,
	   gnome_canvas_pixbuf_get_type (),
	   "x", x, "y", y,
	   "width", 1.0, "height", 1.0,
	   "width_set", TRUE, "height_set", TRUE,
	   "pixbuf", pb,
	   NULL);
   gdk_pixbuf_unref (pb);

   gtk_signal_connect (GTK_OBJECT (image), "event",
	   (GtkSignalFunc) board_press_cb, NULL);

   return image;
}

    static GnomeCanvasItem *
board_draw_background (Board *board, double x, double y)
{
   BoardPrivate *priv;
   GnomeCanvasItem *image = NULL;
   GnomeCanvasGroup *root;
   gint f;

   priv = board->priv;
   f = get_square (x, y, priv->flip);

   root = GNOME_CANVAS_GROUP (gnome_canvas_root (GNOME_CANVAS (board)));

   image = gnome_canvas_item_new (root,
	   gnome_canvas_rect_get_type (),
	   "x1", x,
	   "y1", y,
	   "x2", x + 0.99,
	   "y2", y + 0.99,
	   "fill_color_rgba", 
	   (((int)(x+y)) % 2) ? priv->dark_rgba : priv->light_rgba,
	   NULL);

   gtk_signal_connect (GTK_OBJECT (image), "event",
	   (GtkSignalFunc) board_press_cb,
	   GINT_TO_POINTER (f));

   return image;
}



    static void 
board_draw (Board *board)
{
   BoardPrivate *priv;
   int i,j;

   priv = board->priv;

   for (i = 0; i < 8; i++)
      for (j = 0; j < 8; j++)
	 priv->squares[i * 8 + j] = board_draw_background (board, i, j);

   gnome_canvas_set_scroll_region (GNOME_CANVAS (board), 0, 0, priv->size, priv->size);
}

    static void
board_update (Board *board) 
{
   BoardPrivate *priv;
   int n, n2, i, j;

   priv = board->priv;

   for (i = 0; i < 8; i++)
      for (j = 0; j < 8; j++) {
	 n  = H8 - i * 10 - j;
	 if (!priv->flip) 
	    n2 = n;
	 else
	    n2 = A1 + i*10 + j;

	 if (priv->pos->square[n2] != priv->db[n]) {
	    if (priv->db_image[n])
	       gtk_object_destroy (GTK_OBJECT (priv->db_image[n]));
	    priv->db_image[n] = board_draw_piece (board, n, priv->pos->square[n2]);
	    priv->db[n] = priv->pos->square[n2];
	 }
      }
}

    static void
destroy (GtkObject *obj)
{
   Board *board;
   BoardPrivate *priv;

   board = BOARD (obj);
   priv = board->priv;

   gtk_object_unref (GTK_OBJECT (priv->pos));
   g_free (priv);

   GTK_OBJECT_CLASS (parent_class)->destroy (obj);
}

