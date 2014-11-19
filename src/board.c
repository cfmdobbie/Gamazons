#include <time.h>
#include <assert.h>
#include <gnome.h>

#include "amazons.h"
#include "board.h"
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
extern GtkWidget *main_window;
extern int new_game;
Square legal_moves[100];
int state_hash;

void init_game_board(GtkWidget *GamazonsMain)
{
   int i,j;
   char color[256];
   GtkWidget *w = (GtkWidget *) lookup_widget(GamazonsMain, BOARD_NAME);
   GtkWidget *force_button;
   

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

   force_button = (GtkWidget *)lookup_widget(main_window, "BT_FORCEMOVE");
   gtk_widget_set_sensitive (force_button, FALSE);
   
   draw_board();
   what_next = MOVE_WHITE_QUEEN;


}


void fill_a_square(GnomeCanvasGroup *group,
       	double x1, double y1, double x2, double y2, char *color)
{
   /* draw a box*/
   gnome_canvas_item_new(group,
	   gnome_canvas_rect_get_type(),
	   "x1", x1,
	   "y1", y1,
	   "x2", x2,
	   "y2", y2,
	   "outline_color", "black",
	   "fill_color", color,
	   "width_pixels", (double)THICKNESS,
	   NULL, NULL);

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
   

   white_pb = gdk_pixbuf_new_from_file(PACKAGE_DATA_DIR "/pixmaps/white.png", NULL);
   if (white_pb == NULL)
     {
      fprintf(stderr, "Cannot find white.png\n");
      exit(1);
     }

   black_pb = gdk_pixbuf_new_from_file(PACKAGE_DATA_DIR "/pixmaps/black.png", NULL);
   if (black_pb == NULL)
     {
      fprintf(stderr, "Cannot find black.png\n");
      exit(1);
     }



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
   double to_Lx, to_Uy;
   int x, y;
   int inc = 1;
   int i,j;

   to_Lx = get_x_from_square(board->to);
   to_Uy = get_y_from_square(board->to);
      
   printf("We want the queen at coords %f, %f\n", to_Lx, to_Uy);
   gnome_canvas_item_get_bounds(item, &Lx, &Uy, &Rx, &By);
   printf("The queen is at coords %f, %f\n", Lx, Uy);
   while (Lx != to_Lx || Uy != to_Uy)
     {
      if (Lx < to_Lx)
	 x = inc;
      else if (Lx > to_Lx)
	 x = -inc;
      else
	 x = 0;

      if (Uy < to_Uy)
	 y = inc;
      else if (Uy > to_Uy)
	 y = -inc;
      else
	 y = 0;


      gnome_canvas_item_move (item, (double)x, (double)y);
      gnome_canvas_item_raise_to_top (item);

      //update the board
      while (gtk_events_pending())
	 gtk_main_iteration();

      gnome_canvas_item_get_bounds(item, &Lx, &Uy, &Rx, &By);
     }

   /*
   gnome_canvas_item_move (item, 
	   to_Lx - Lx,
	   to_Uy - Uy);
	   */

   gnome_canvas_item_raise_to_top (item);
	   //see where it landed
   gnome_canvas_item_get_bounds(item, &Lx, &Uy, &Rx, &By);
   printf("The queen landed at coords %f, %f\n", Lx, Uy);
   printf("this time the queen is on square %d\n", board->to);
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
 * move process, and checks for a win afterwards.  If not, it just checks for 
 * the win.  Returns TRUE if an AI opponent moves next.  False if human.
 *
 * NOTE: If you have 2 AI players, this function would just keep thinking and 
 * never let the board update or respond.  So there are several checks to see
 * if any new events occured that should be handled, or critical changes have
 * been made (like starting a new game, etc..).  If something critical has changed
 * the function will exit after learning about it.
 */
int move_ai()
{
   state *s = states.s[states.current_state];
   move temp;
   move movelist[3000];
   int ai = FALSE;
   int current_hash;
   GtkWidget *auto_button, *force_button;

   current_hash = state_hash = create_hash(s);

   //It's sometimes necessary to know if we're in the middle of a move, because
   //if an event causes another move to start and that event is processed and then
   //this function finishes, it leaves the board in an unstable result

   //XXX This should call a function to disable certain event handling instead of
   //just having a silly global variable.  For instance, it could gray out the
   //Auto Finish button so the user knows it's not going to do anything when he 
   //presses it.  Perhaps the 'Force Move' button should be greyed out until the AI
   //is thinking, or since Force Move & Auto Finish are mutually exclusive, it would
   //be cool to have the button switch labels depending on the state of the game.
   auto_button = (GtkWidget *) lookup_widget(main_window, "BT_AUTOFINISH");
   force_button = (GtkWidget *) lookup_widget(main_window, "BT_FORCEMOVE");
   gtk_widget_set_sensitive (auto_button, FALSE);
   gtk_widget_set_sensitive (force_button, TRUE);



   //update the board
   while (gtk_events_pending())
      gtk_main_iteration();
   if (current_hash != state_hash)
      return FALSE;

   //quit this function if a 'New Game' option was selected since this
   //function was started.
   if (new_game)
     {
      new_game = FALSE;
      return FALSE;
     }

   //gnome_canvas_item_request_update(board->canvas);
   if (((states.s[states.current_state]->turn == WHITE_PLAYER) && (options.white_player == AI)) ||
       ((states.s[states.current_state]->turn == BLACK_PLAYER) && (options.black_player == AI)))
     {
      what_next = WAIT_FOR_AI;
      ok = 1;
      ai = TRUE;
      start = time(NULL);
      temp = isearch(s, NOTHINK);
      if (s->winner)
	 return FALSE;
      makemove(s,temp);

      //update the board before drawing the new move
      //the program would segfault if you closed it while it was thinking
      while (gtk_events_pending())
	 gtk_main_iteration();
      if (current_hash != state_hash)
	 return FALSE;

      if (new_game)
	{
	 new_game = FALSE;
	 return FALSE;
	}

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
   if (options.white_player == AI)
      printf("White is AI\n");
   if (options.black_player == AI)
      printf("Black is AI\n");
   printf("Turn is %d\n", states.s[states.current_state]->turn );

   //check for gameover
   /*
   if (children(s, movelist) == 0)
     {
      //printf("player %d wins!\n", s->turn^3);
      s->winner = s->turn^3;
      if (s->winner == BLACK)
	 gnome_ok_dialog("White wins!");
      else
	 gnome_ok_dialog("Black wins!");
     }
     */
   if (game_over(movelist))
     {
      //XXX should I set ai = FALSE?
     }


   gtk_widget_set_sensitive (auto_button, TRUE);
   gtk_widget_set_sensitive (force_button, FALSE);
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

   printf("Can't move to square.  Legal moves are: %d\n", sq);
   i=0;
   while (legal_moves[i] < 100)
      printf(" %d", legal_moves[i++]);
   printf("\n");
   return FALSE;
}

/*==============================================================================
 * count_queens
 *
 * DEBUG - counts the number of queens on the GUI representation and prints
 * out a bunch of XXXX's whenever there are not 4 of both kinds.
 */ 
void count_queens()
{
   int black=0, white=0;
   int i,j;

   for(i=0; i<10; i++)
     {
      for(j=0; j<10; j++)
	{
	 if (board->squares[i][j] == WHITE)
	    white++;
	 if (board->squares[i][j] == BLACK)
	    black++;
	}
     }
   if (black > 4) 
      printf("YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY\n");
   if (white > 4)
      printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
   if (black < 4)
      printf("XYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYX\n");
   if (white < 4)
      printf("ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ\n");
}



/*==============================================================================
 * free_all_memory
 *
 * When a new game is started, we want to free all the memory we've allocated
 * so we can start all over without leaking all the memory.
 */
void free_all_memory()
{
   int i;

   //free states
   for (i=0; i< states.max_state; i++)
      free (states.s[i]);

   //Oh, this is ugly!  Do I really want to do this?
   /*
   if(tt)
     {
      for (i=0; i<TT; i++)
       	{
	 if (tt[i])
	    free(tt[i]);
       	}
     }
     */



}


/*==============================================================================
 * create_hash
 *
 * Creates a hash value for the current state.  On the GUI side it's used to 
 * see if the state has changed recently.
 */
int create_hash(state *s)
{

   ull board_u, board_l;

   board_u = s->white_bd[1] | s->black_bd[1] | s->blocks_bd[1];
   board_l = s->white_bd[0] | s->black_bd[0] | s->blocks_bd[0];

   return( (board_u ^ board_l) % TT);
}


/*==============================================================================
 * game_over
 *
 * Checks to see if the game is over and generates a pop-up stating who the 
 * winner is.  Returns TRUE if the game is over.
 */
int game_over(move *movelist)
{
   state *s = states.s[states.current_state];

   if (children(s, movelist) == 0)
     {
      //printf("player %d wins!\n", s->turn^3);
      s->winner = s->turn^3;
      if (s->winner == BLACK)
	 gnome_ok_dialog("White wins!");
      else
	 gnome_ok_dialog("Black wins!");

      return TRUE;
     }
   else
      return FALSE;

}

