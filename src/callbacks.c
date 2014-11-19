#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gnome.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "amazons.h"
#include "board.h"

extern Board *board;
extern struct options options;
extern struct game_states states;
extern int what_next;
extern Square legal_moves[100];
extern int ok;
extern GtkWidget *main_window;
extern state_hash;
int grabbed_queen;

int allow_auto_finish;
GtkWidget *PlayerSettingsWindow;


void
on_new1_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
   free_all_memory();
   init_engine();
   init_game_board(main_window);
   while (move_ai());  //if both players are AI, keeps on running
}


void
on_open1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_save1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_save_as1_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_quit1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

   state_hash = 0;
   gtk_main_quit();

}


void
on_cut1_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_copy1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_paste1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_clear1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_properties1_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_preferences1_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_about1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_undo_move2_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_redo_move3_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}


void
on_network1_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_player1_activate                    (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
   GtkWidget *time, *width, *depth;
   GtkWidget *white_ai, *white_h, *black_ai, *black_h;


   PlayerSettingsWindow = create_PlayerSettings();

   /* grab all the widgets */
   time = lookup_widget(PlayerSettingsWindow, "TimeSpinner");
   width = lookup_widget(PlayerSettingsWindow, "WidthSpinner");
   depth = lookup_widget(PlayerSettingsWindow, "DepthSpinner");
   white_ai = lookup_widget(PlayerSettingsWindow, "WhiteAIRadio");
   white_h = lookup_widget(PlayerSettingsWindow, "WhiteHumanRadio");
   black_ai = lookup_widget(PlayerSettingsWindow, "BlackAIRadio");
   black_h = lookup_widget(PlayerSettingsWindow, "BlackHumanRadio");


   /* Load current values */
   gtk_spin_button_set_value( (GtkSpinButton *)time, options.engine.timeout);
   gtk_spin_button_set_value( (GtkSpinButton *)width, options.engine.maxwidth);
   gtk_spin_button_set_value( (GtkSpinButton *)depth, options.engine.maxdepth);

   if (options.white_player == HUMAN)
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(white_h), TRUE);
   else
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(white_ai), TRUE);

   if (options.black_player == HUMAN)
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(black_h), TRUE);
   else
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(black_ai), TRUE);


   gtk_widget_show(PlayerSettingsWindow);

}


void
on_how_to_play1_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_help2_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_BT_UNDO_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{

}


/*==============================================================================
 * on_BT_FORCEMOVE_clicked
 *
 * This sets the global timeout variable, forcing the AI to take the best move
 * currently available.
 */
void
on_BT_FORCEMOVE_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
   ok = 0;
}


void
on_BT_AUTOFINISH_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
   if (allow_auto_finish)
     {
      options.white_player = AI;
      options.black_player = AI;
      options.engine.timeout = 1;
      options.engine.maxwidth = 15;
      while (move_ai());  //if both players are AI, keeps on running
     }

}


void
on_GamazonsMain_destroy                (GtkObject       *object,
                                        gpointer         user_data)
{

   state_hash = 0;
   gtk_main_quit(); 

}


int
board_press_cb (GnomeCanvasItem *item, GdkEvent *event, gpointer data)
{
   double drop_x, drop_y;
   double new_x, new_y;
   int from_row, from_col, to_row, to_col;
   int from;
   int i,j;


   //printf("MainEvent = %d\n", event);
   if (data) {
      item = board->db_image [GPOINTER_TO_INT (data)];
      if (item == NULL && event->type != GDK_BUTTON_RELEASE) 
	 return 0;
   }

   switch (event->type) {
       case GDK_BUTTON_PRESS:
	   if (event->button.button != 1)
	      break;	

	   printf("what_next = %d\n", what_next);
	   board->orig_x = board->curr_x = event->button.x;
	   board->orig_y = board->curr_y = event->button.y;
	   from = get_square (board->curr_x, board->curr_y);
	   from_col = get_x_int_from_square(from);
	   from_row = get_y_int_from_square(from);

//DEBUG: print board
   for (i=0; i<BOARD_SIZE; i++)
     {
      for (j=0; j<BOARD_SIZE; j++)
	{
	 printf(" %d", board->squares[i][j]);
	}
      printf("\n");
     }

	   //Make sure it's time to move a queen before letting the user do it,
	   //as well as make sure he's moving his own queen

	   printf("checking row %d, col %d\n", from_row, from_col);
	   square_contains(from);
	   printf("board->squares = %d\n",board->squares[from_row][from_col]);
	   if ((board->squares[from_row][from_col] == WHITE && what_next == MOVE_WHITE_QUEEN) ||
	       (board->squares[from_row][from_col] == BLACK && what_next == MOVE_BLACK_QUEEN))
	     {
	      //Human is moving a queen
	      printf("board->squares = %d, what_next = %d\n", board->squares[from_row][from_col], what_next);
	      grabbed_queen = TRUE;
	      gen_legal_moves(from);
	      printf("grabbing queen\n");
	      gnome_canvas_item_raise_to_top (item);
	      gnome_canvas_item_grab (item,
		      GDK_POINTER_MOTION_MASK | 
		      GDK_BUTTON_RELEASE_MASK,
		      NULL,
		      event->button.time);

	      board->selected_queen = item;
	     }
	   board->from = get_square (board->curr_x, board->curr_y);
	   board->to = board->from;
	   printf("GDK_BUTTON_PRESS: board->to = %d  board->from = %d\n", board->to, board->from);
	   break;

       case GDK_MOTION_NOTIFY:
	   if (event && (event->motion.state & GDK_BUTTON1_MASK)) 
	     {
	      if (!grabbed_queen)
		 break;
	      new_x = event->motion.x;
	      new_y = event->motion.y;
	      gnome_canvas_item_raise_to_top (item);
	      gnome_canvas_item_move (item, 
		      new_x - board->curr_x,
		      new_y - board->curr_y);

	      /*
	      if (board->selected != NULL)
		 clear_square (&board->selected);
		 */

	      board->curr_x = new_x;
	      board->curr_y = new_y;
	     }
	   break;

       case GDK_BUTTON_RELEASE:
	   if (event->button.button != 1)
	      break;
	   printf("what_next = %d\n", what_next);
	   if (grabbed_queen == FALSE)
	      break;
	   else
	      grabbed_queen = FALSE;

	   if (item != NULL)
	      gnome_canvas_item_ungrab (item, event->button.time);


	   printf("GDK_BUTTON_RELEASE: board->to = %d  board->from = %d\n", board->to, board->from);
	   drop_x = event->button.x;
	   drop_y = event->button.y;

	   //something funny here?
	   if (is_queen_square(get_square (drop_x, drop_y)))
	     {
	      try_move (board, item);
	      break;
	     }

	   printf("Queen is dropped at coords %f, %f\n", drop_x, drop_y);
	   board->to = get_square (drop_x, drop_y);
	   printf("new square is %d\n", board->to);
	   /*
	   if (board->to == board->from && board->selected == NULL) {
	      board->selected = board->squares [(int)drop_x * 8 + (int)drop_y];

	      mark_square (board->selected);
	      gnome_canvas_item_move (item, 
		      board->orig_x - board->curr_x,
		      board->orig_y - board->curr_y);

	      printf("queen is now on square %d\n", board->to);
	      board->selected_from = board->from;
	      break;
	      
	      */
	   //} else 
	    //  if (board->to == board->from) 
	//	 break;
	      //board->from = board->selected_from;
	
	   /* Register the queen move with the board */
	   from_col = get_x_int_from_square(board->from);
	   from_row = get_y_int_from_square(board->from);

	   to_col = get_x_int_from_square(board->to);
	   to_row = get_y_int_from_square(board->to);
	   printf("setting square %d%d to hold %d\n", to_row, to_col, board->squares[from_row][from_col]);

	   //Queen is being moved to a different square
	   if (board->to != board->from) 
	     {
	      //put the piece back if it's not a legal move
	      if (!is_move_legal(board->to))
		{
		 board->to = board->from;
		 try_move(board, item);
		 break;
		}
	      else
		{
		 what_next = FIRE_ARROW;
		 allow_auto_finish = FALSE;
		 board->squares[to_row][to_col] = board->squares[from_row][from_col];
		 board->squares[from_row][from_col] = NOTHING;
		 gen_legal_moves(board->to); //prepare moves for arrow
		}
	     }

	   square_contains(board->to);
	   square_contains(board->from);


	   try_move (board, item);
	   /*
	   if (board->selected)
	      clear_square (&board->selected);
	      */
	   printf("what_next = %d\n", what_next);
	   break;
       default:
   }

   return 1;
}

/*==============================================================================
 * arrow_fire_cb
 *
 * Determines the square the arrow is fired at and marks it as such.
 * Also checks that this is the appropriate time to fire an arrow and that the
 * given square is in the list of legal moves.
 */
int arrow_fire_cb(GnomeCanvasItem *item, GdkEvent *event, gpointer data)
{
   double x_coord, y_coord;
   int sq;
   int row, col;
   state *s;
   move movelist[3000];

   count_queens();
   switch (event->type) 
     {
       case GDK_BUTTON_PRESS:
	   if (event->button.button != 1)
	      break;	
	   if (what_next != FIRE_ARROW)
	      break;

	   x_coord = event->button.x-8;
	   y_coord = event->button.y-15;

	   sq = get_square(x_coord, y_coord);
	   if (!is_move_legal(sq))
	      break;

	   /* Make sure the square is empty first */
	   col = get_x_int_from_square(sq);
	   row = get_y_int_from_square(sq);

	   printf("what_next = %d\n", what_next);
	   printf("arrow fire:  ");
	   square_contains(sq);
	   if (board->squares[row][col] != NOTHING)
	      break;

	   fire_arrow(sq);
	   s = states.s[states.current_state];
	   register_move_with_engine(sq);

	   if (s->turn == WHITE_PLAYER)
	     {
	      what_next = MOVE_WHITE_QUEEN;
	      printf("white moves next\n");
	     }
	   else if (s->turn == BLACK_PLAYER)
	     {
	      what_next = MOVE_BLACK_QUEEN;
	      printf("black moves next\n");
	     }
	   else
	      printf("XXXXXXXXXXXXXXX  BLARGH!  I don't know who's turn it is!\n");

	   //check for gameover
	   if (children(s, movelist) == 0)
	     {
	      printf("player %d wins!\n", s->turn^3);
	      s->winner = s->turn^3;
	      break;
	     }

	   allow_auto_finish = TRUE;
	   dup_state(s, states.s[++(states.current_state)]);
	   move_ai();
       default:
     }

   return 0;

}

void
on_PlayerOKButton_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
   GtkWidget *time, *width, *depth;
   GtkWidget *white_ai, *white_h, *black_ai, *black_h;


   /* grab all the widgets */
   time = lookup_widget(PlayerSettingsWindow, "TimeSpinner");
   width = lookup_widget(PlayerSettingsWindow, "WidthSpinner");
   depth = lookup_widget(PlayerSettingsWindow, "DepthSpinner");
   white_ai = lookup_widget(PlayerSettingsWindow, "WhiteAIRadio");
   white_h = lookup_widget(PlayerSettingsWindow, "WhiteHumanRadio");
   black_ai = lookup_widget(PlayerSettingsWindow, "BlackAIRadio");
   black_h = lookup_widget(PlayerSettingsWindow, "BlackHumanRadio");

   /* Store new values */
   options.engine.timeout = gtk_spin_button_get_value_as_int( (GtkSpinButton *)time);
   options.engine.maxwidth = gtk_spin_button_get_value_as_int( (GtkSpinButton *)width);
   options.engine.maxdepth = gtk_spin_button_get_value_as_int( (GtkSpinButton *)depth);

   if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(white_h)))
      options.white_player = HUMAN;
   else
      options.white_player = AI;

   if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(black_h)))
      options.black_player = HUMAN;
   else
      options.black_player = AI;

   store_values_in_file();
   gtk_widget_destroy(PlayerSettingsWindow);

   //checks to see if the AI is supposed to move after changes to the player have been made
   while(move_ai());



}


void
on_PlayerCancelButton_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
   gtk_widget_destroy(PlayerSettingsWindow);

}

