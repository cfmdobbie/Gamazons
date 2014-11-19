#include <time.h>
#include <assert.h>
#include <gtk/gtk.h>
#include <gnome.h>

#include "amazons.h"
#include "board.h"
#include "position.h"
#include "makros.h"
#include "callbacks.h"

/* local Prototypes */


static void fill_a_square(GnomeCanvasGroup *group,
       	double x1, double y1, double x2, double y2, char *color);
static void get_square_color(int square, char *color);

/* Globals */
int what_next;	//
extern Board *board;
extern struct options options;
extern struct game_states states;
extern int ok;
extern time_t start;
Square legal_moves[100];

void init_game_board(GtkWidget *GamazonsMain)
{
   int i,j;
   char color[256];
   GtkWidget *w = lookup_widget(GamazonsMain, BOARD_NAME);
   

   board = (Board *) malloc(sizeof(Board));
   board->canvas = GNOME_CANVAS(w);

   /* set where can the canvas scroll (our usable area) */
   gnome_canvas_set_scroll_region(board->canvas, 0.0, 0.0,
	   BOARD_SIZE*CELL_SIZE + 2*BOARD_BORDER,
	   BOARD_SIZE*CELL_SIZE + BOARD_BORDER);

   /* set the size of the widget */
   gtk_widget_set_usize(w,
	   BOARD_SIZE*CELL_SIZE + 2*BOARD_BORDER,
	   BOARD_SIZE*CELL_SIZE + BOARD_BORDER);


   /* initialize pieces */
   for (i=0; i<BOARD_SIZE; i++)
     {
      for (j=0; j<BOARD_SIZE; j++)
	{
	 board->squares[i][j] = NOTHING;
	}
     }
   gtk_signal_connect(GTK_OBJECT(board->canvas), "event",
	   GTK_SIGNAL_FUNC(arrow_fire_cb), NULL);
/*
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
*/



   /*
   board->squares[3][9] = WHITE;
   board->squares[6][9] = WHITE;
   board->squares[0][6] = WHITE;
   board->squares[9][6] = WHITE;

   board->squares[3][0] = BLACK;
   board->squares[6][0] = BLACK;
   board->squares[0][3] = BLACK;
   board->squares[9][3] = BLACK;
   */
   board->squares[9][3] = WHITE;
   board->squares[9][6] = WHITE;
   board->squares[6][0] = WHITE;
   board->squares[6][9] = WHITE;

   board->squares[0][3] = BLACK;
   board->squares[0][6] = BLACK;
   board->squares[3][0] = BLACK;
   board->squares[3][9] = BLACK;

   draw_board();
   what_next = MOVE_WHITE_QUEEN;


}

static void
draw_a_line(GnomeCanvasGroup *group,
       	int x1, int y1, int x2, int y2, char *color)
{
   GnomeCanvasPoints *points;

   /* allocate a new points array */
   points = gnome_canvas_points_new (2);

   /* fill out the points */
   points->coords[0] = x1;
   points->coords[1] = y1;
   points->coords[2] = x2;
   points->coords[3] = y2;
   /* draw the line */
   gnome_canvas_item_new(group,
	   gnome_canvas_line_get_type(),
	   "points", points,
	   "fill_color", color,
	   "width_units", (double)THICKNESS,
	   NULL);

   /* free the points array */
   gnome_canvas_points_free(points);
}

void fill_a_square(GnomeCanvasGroup *group,
       	double x1, double y1, double x2, double y2, char *color)
{
   /* draw the line */
   gnome_canvas_item_new(group,
	   GNOME_TYPE_CANVAS_RECT,
	   "x1", x1,
	   "y1", y1,
	   "x2", x2,
	   "y2", y2,
	   "outline_color", "black",
	   "fill_color", color,
	   "width_pixels", (double)THICKNESS,
	   NULL);

}

static void get_square_color(int square, char *color)
{
   if ((square % 2) == 0)
      strcpy(color, SQUARE_COLOR_1);
   else
      strcpy(color, SQUARE_COLOR_2);
}


void draw_board()
{
   int i,j;
   int black_i = 0;
   GdkPixbuf *white_pb, *black_pb;
   char color[256];
   GnomeCanvasItem *image;
   GnomeCanvasGroup *root = GNOME_CANVAS_GROUP(gnome_canvas_root (GNOME_CANVAS (board->canvas)));
   


   white_pb = gdk_pixbuf_new_from_file("/home/yorgasor/Projects/Gamazons/src/white.png", NULL);
   if (white_pb == NULL)
      printf("error loading white.png\n");
   else
      printf("loaded white.png just fine\n");
   black_pb = gdk_pixbuf_new_from_file("/home/yorgasor/Projects/Gamazons/src/black.png", NULL);
   if (black_pb == NULL)
      printf("error loading black.png\n");

   /* fill alternate squares */
   for(j=0;j<BOARD_SIZE;j++) 
     {
      for(i=0;i<BOARD_SIZE;i++) 
	{
	 image = NULL;
	 get_square_color(i+j, color);
	 fill_a_square(gnome_canvas_root(board->canvas),
		 BOARD_BORDER + i*CELL_SIZE,
		 BOARD_BORDER + j*CELL_SIZE,
		 BOARD_BORDER + i*(CELL_SIZE) + CELL_SIZE,
		 BOARD_BORDER + j*(CELL_SIZE) + CELL_SIZE,
		 color);
	 if (board->squares[j][i] == WHITE)
	   {
	    printf("Square %dx%d contains a white queen\n",i,j);
	    image = gnome_canvas_item_new (root,
		    gnome_canvas_pixbuf_get_type (),
		    "x", i*CELL_SIZE+QUEEN_OFFSET, "y", j*CELL_SIZE+QUEEN_OFFSET,
		    "width", CELL_SIZE, "height", CELL_SIZE,
		    "width_set", TRUE, "height_set", TRUE,
		    "pixbuf", white_pb,
		    NULL);
	    //We need to do some funky checking to make sure board->white_queens[] matches
	    //up exactly with state->white_q_x[], state->white_q_y[]
	    if(i == 0)
	      {
	       board->white_queens[2] = image;
	       printf("registering queen 2\n");
	      }
	    else if (i == 3)
	      {
	       board->white_queens[1] = image;
	       printf("registering queen 1\n");
	      }
	    else if (i == 6)
	      {
	       board->white_queens[0] = image;
	       printf("registering queen 0\n");
	      }
	    else if (i == 9)
	      {
	       board->white_queens[3] = image;
	       printf("registering queen 3\n");
	      }
	   }
	 else if (board->squares[j][i] == BLACK)
	   {
	    printf("Square %dx%d contains a black queen\n",i,j);
	    image = gnome_canvas_item_new (root,
		    gnome_canvas_pixbuf_get_type (),
		    "x", i*CELL_SIZE+QUEEN_OFFSET, "y", j*CELL_SIZE+QUEEN_OFFSET,
		    "width", CELL_SIZE, "height", CELL_SIZE,
		    "width_set", TRUE, "height_set", TRUE,
		    "pixbuf", black_pb,
		    NULL);
	    //miraculously, these already match up perfectly so no funky stuff needed here
	    board->black_queens[black_i++] = image;
	   }

	 if (image != NULL)
	   {
	    printf("connecting signal to queen\n");
	    gtk_signal_connect(GTK_OBJECT(image), "event",
		    GTK_SIGNAL_FUNC(board_press_cb), NULL);
	    printf("connected signal to queen\n");
	   }


	}
     }
   /*
   image = gnome_canvas_item_new (root,
	   gnome_canvas_pixbuf_get_type (),
	   "x", 10.0, "y", 10.0,
	   "width", 40.0, "height", 40.0,
	   "width_set", TRUE, "height_set", TRUE,
	   "pixbuf", white_pb,
	   NULL);
	   */

}



void mark_square (GnomeCanvasItem *square)
{
   gnome_canvas_item_set (square, "outline_color", "red", NULL);
}

Square get_square (double x, double y)
{
   Square from;
   int x_square;
   int y_square;

   x -= BOARD_BORDER;
   y -= BOARD_BORDER;

   if (x < 0)
      x = 0.0;
   if (y < 0)
      y = 0.0;

   x_square = x / 40;
   y_square = y / 40;

   printf("x coord = %f   y coord = %f\n", x, y);
   printf("x coord = %d   y coord = %d\n", x_square, y_square);

   from = x_square + y_square * 10;
   /*
   if (!flip)
      from = A1 + (Square)x  + 10 * (9 - (Square)y);
   else
      from = J10 - (Square)x - 10 * (9 - (Square)y);
      */
   

   return from;
}

void clear_square (GnomeCanvasItem **square)
{
   gnome_canvas_item_set (*square, "outline_color", NULL, NULL);
   *square = NULL;
}

void try_move (Board *board, GnomeCanvasItem *item)
{
   double Lx, Uy, Rx, By;

   //board->to = position_move_normalize (board->pos, board->from, board->to);
   //if (board->to) {
    //  position_move (board->pos, board->from, board->to);
    //  board_update (board);
      //draw_board();
      /*
      gtk_signal_emit (GTK_OBJECT (board),
	      board_signals [MOVE_SIGNAL],
	      board->from,
	      board->to);
	      */
      printf("We want the queen at coords %f, %f\n", 
	      get_x_from_square(board->to),
	      get_y_from_square(board->to));
      gnome_canvas_item_get_bounds(item, &Lx, &Uy, &Rx, &By);
      printf("The queen is at coords %f, %f\n", Lx, Uy);
      gnome_canvas_item_move (item, 
	      get_x_from_square(board->to) - Lx,
	      get_y_from_square(board->to) - Uy);
      gnome_canvas_item_raise_to_top (item);
      //see where it landed
      gnome_canvas_item_get_bounds(item, &Lx, &Uy, &Rx, &By);
      printf("The queen landed at coords %f, %f\n", Lx, Uy);
      printf("this time the queen is on square %d\n", board->to);
      /*
   } else if (item != NULL) {
      gnome_canvas_item_move (item,
	      board->orig_x - board->curr_x,
	      board->orig_y - board->curr_y);

   }
   */
}


double get_x_from_square(int sq)
{
   double x;

   x = (double) ((sq % 10) * CELL_SIZE+QUEEN_OFFSET);

   return x;

}

double get_y_from_square(int sq)
{
   double y;

   y = (double) ((sq / 10) * CELL_SIZE+QUEEN_OFFSET);

   return y;


}

int get_x_int_from_square(int sq)
{
   return(sq % 10);
}

int get_y_int_from_square(int sq)
{
   return(sq / 10);
}

int engine_x_to_board_x(int eng_x)
{
   return(eng_x);//hey, these are the same, no conversion necessary
}

int engine_y_to_board_y(int eng_y)
{
   return(9 - eng_y);
}

int board_x_to_engine_x(int brd_x)
{
   return(brd_x);
}

int board_y_to_engine_y(int brd_y)
{
   return(9 - brd_y);
}

int get_square_from_engine(int x, int y)
{
   return((9 - y) * 10 + x);
}


void fire_arrow(Square sq)
{
   int x,y;

   x = sq % 10;
   y = sq / 10;

   board->squares[y][x] = ARROW;

   fill_a_square(gnome_canvas_root(board->canvas),
	   BOARD_BORDER + x*CELL_SIZE,
	   BOARD_BORDER + y*CELL_SIZE,
	   BOARD_BORDER + x*(CELL_SIZE) + CELL_SIZE,
	   BOARD_BORDER + y*(CELL_SIZE) + CELL_SIZE,
	   "black");
}

void square_contains(Square sq)
{
   int row, col;

   col = get_x_int_from_square(sq);
   row = get_y_int_from_square(sq);

   if (board->squares[row][col] == NOTHING)
      printf("Nothing is found at square %d\n", sq);
   else if (board->squares[row][col] == WHITE)
      printf("A White Queen is found at square %d\n", sq);
   else if (board->squares[row][col] == BLACK)
      printf("A Black Queen is found at square %d\n", sq);
   else if (board->squares[row][col] == ARROW)
      printf("An arrow is found at square %d\n", sq);
   else
      printf("Whoa, I don't know _what_ is on square %d\n", sq);
}


/*==============================================================================
 * move_ai
 *
 * Checks to see if an AI oppenent is next to move.  If it is, it starts the 
 * move process.  If not,
 *
 */
int move_ai()
{
   state *s = states.s[states.current_state];
   move temp;
   int ai = FALSE;

   while (gtk_events_pending())
      gtk_main_iteration();

   //gnome_canvas_item_request_update(board->canvas);
   if (((states.s[states.current_state]->turn == WHITE_PLAYER) && (options.white_player == FALSE)) ||
       ((states.s[states.current_state]->turn == BLACK_PLAYER) && (options.black_player == FALSE)))
     {
      what_next = WAIT_FOR_AI;
      ok = 1;
      ai = TRUE;
      start = time(NULL);
      temp = isearch(s, NOTHINK);
      if (s->winner)
	 return FALSE;
      makemove(s,temp);
      //register move on graphical board
      move_piece(temp);
      dup_state(s, states.s[++(states.current_state)]);
      if (s->turn == WHITE_PLAYER)
	 what_next = MOVE_WHITE_QUEEN;
      if (s->turn == BLACK_PLAYER)
	 what_next = MOVE_BLACK_QUEEN;
     }
   else
     {
      printf("the AI doesn't move next:\n");
     }
   if (options.white_player == FALSE)
      printf("White is AI\n");
   if (options.black_player == FALSE)
      printf("Black is AI\n");
   printf("Turn is %d\n", states.s[states.current_state]->turn );

   return ai;
}

/*==============================================================================
 * move_piece
 *
 * Takes a move struct generated by the engine, and extracts the necessary info
 * to update the GUI data structs and have the GUI reflect the move.
 */
void move_piece(move m)
{
   GnomeCanvasItem *item;
   int from_row, from_col;
   int to_row, to_col;

   board->to = get_square_from_engine(m.tocol, m.torow);
   to_col = get_x_int_from_square(board->to);
   to_row = get_y_int_from_square(board->to);
   //Note: by the time the state gets here, it's signaled the other player's turn
   //so if it says it's white's turn, black just moved and we need to move black's
   //piece.
   if (states.s[states.current_state]->turn == WHITE_PLAYER)
     {
      board->from = get_square_from_engine(states.s[states.current_state -1]->black_q_x[m.queen],
	      states.s[states.current_state -1]->black_q_y[m.queen]);
      
      board->squares[to_row][to_col] = BLACK;
      printf("Moving black queen\n");
      item = board->black_queens[m.queen];
     }
   else
     {
      board->from = get_square_from_engine(states.s[states.current_state -1]->white_q_x[m.queen],
	      states.s[states.current_state -1]->white_q_y[m.queen]);
      board->squares[to_row][to_col] = WHITE;
      printf("Moving white queen\n");
      item = board->white_queens[m.queen];
     }


   from_col = get_x_int_from_square(board->from);
   from_row = get_y_int_from_square(board->from);
   board->squares[from_row][from_col] = NOTHING;

   try_move(board, item);
   printf("Engine coords for arrow: %d, %d\n", m.wallcol, m.wallrow);
   fire_arrow(get_square_from_engine(m.wallcol, m.wallrow));
   printf("fired arrow to square %d\n", get_square_from_engine(m.wallcol, m.wallrow));
   pmove(m);
}

/*==============================================================================
 * register_move_with_engine
 *
 * Fills out a move struct with the human's move and calls makemove() to update
 * the state struct, so the AI engine knows what happened.
 */
void register_move_with_engine(Square arrow_sq)
{
   state *s = states.s[states.current_state];
   move m;
   int i;
   int tocol, torow;
   int found = FALSE;

   //find out the index of the queen that was just moved.  
   //weird things will happen if it's not found.
   for (i=0; i<4; i++)
     {
      if (board->selected_queen == board->white_queens[i] || 
	  board->selected_queen == board->black_queens[i])
	{
	 found = TRUE;
	 break;
	}
     }

   if (!found)
      printf("Yikes!  We didn't find the queen!!\n");

   m.queen = i;
   m.torow = board_y_to_engine_y(get_y_int_from_square(board->to));
   m.tocol = board_x_to_engine_x(get_x_int_from_square(board->to));

   m.wallrow = board_y_to_engine_y(get_y_int_from_square(arrow_sq));
   m.wallcol = board_x_to_engine_x(get_x_int_from_square(arrow_sq));

   makemove(s, m);

}

/*==============================================================================
 * is_queen_square
 *
 * Compares the given square with the information stored in board->squares[][]
 * to see if a queen is there.
 */
int is_queen_square(Square sq)
{
   int row, col;

   col = get_x_int_from_square(sq);
   row = get_y_int_from_square(sq);

   if ((board->squares[row][col] == BLACK) ||
       (board->squares[row][col] == WHITE))
      return TRUE;
   else
      return FALSE;
}


/*==============================================================================
 * gen_legal_moves
 *
 * Given a square, this generates an array of all legal moves that can be made
 * from it.  This works for both queen movement, as well as firing an arrow, 
 * since both move the same way.
 *
 * The array terminator is 100
 */
void gen_legal_moves(Square sq)
{
   int arr_i = 0;
   int i;
   int row, col, sq_row, sq_col;
   int scanning;

   sq_col = get_x_int_from_square(sq);
   sq_row = get_y_int_from_square(sq);

   //make sure the player can drop the piece on the same square if he changes
   //his mind
   legal_moves[arr_i++] = sq;

   //get vertical moves
   row = sq_row + 1;
   col = sq_col;
   while (board->squares[row][col] == NOTHING && row < 10)
     {
      legal_moves[arr_i++] = (row*10) + col;
      row++;
     }

   row = sq_row - 1;
   while (board->squares[row][col] == NOTHING && row >= 0)
     {
      legal_moves[arr_i++] = (row*10) + col;
      row--;
     }

   //get horizontal moves
   row = sq_row;
   col = sq_col + 1;
   while (board->squares[row][col] == NOTHING && col < 10)
     {
      legal_moves[arr_i++] = (row*10) + col;
      col++;
     }

   col = sq_col - 1;
   while (board->squares[row][col] == NOTHING && col >= 0)
     {
      legal_moves[arr_i++] = (row*10) + col;
      col--;
     }

   //get forward diagonal moves
   row = sq_row + 1;
   col = sq_col + 1;
   while (board->squares[row][col] == NOTHING && col < 10 && row < 10)
     {
      legal_moves[arr_i++] = (row*10) + col;
      col++;
      row++;
     }

   row = sq_row - 1;
   col = sq_col - 1;
   while (board->squares[row][col] == NOTHING && col >= 0 && row >= 0)
     {
      legal_moves[arr_i++] = (row*10) + col;
      col--;
      row--;
     }

   //get backward diagonal moves
   row = sq_row + 1;
   col = sq_col - 1;
   while (board->squares[row][col] == NOTHING && col >= 0 && row < 10)
     {
      legal_moves[arr_i++] = (row*10) + col;
      col--;
      row++;
     }

   row = sq_row - 1;
   col = sq_col + 1;
   while (board->squares[row][col] == NOTHING && col < 10 && row >= 0)
     {
      legal_moves[arr_i++] = (row*10) + col;
      col++;
      row--;
     }


   legal_moves[arr_i] = 100;
   printf("legal move list for %d of length %d: \n", sq, arr_i);
   i = 0;
   while (legal_moves[i] < 100)
      printf(" %d", legal_moves[i++]);
   printf("\n");

}

/*==============================================================================
 * is_move_legal
 *
 * Looks up the given square in the current legal_moves array.  If it doesn't 
 * exist, it's not a legal move and returns FALSE.  Returns TRUE if it is there.
 */
int is_move_legal(Square sq)
{
   int i=0;

   printf("checking to see if a move is legal\n");
   while (legal_moves[i] < 100)
     {
      if (sq == legal_moves[i++])
	{
	 printf("%d is a legal move\n", sq);
	 return TRUE;
	}
     }

   printf("can't move to square %d\n", sq);
   return FALSE;
}
