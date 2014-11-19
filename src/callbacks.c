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
extern moving_ai;
int grabbed_queen;
int new_game;
GtkWidget *PlayerSettingsWindow;
extern int moving_ai;

GtkWidget *file_selector;
gchar *selected_filename;

/* Local Prototypes */
static void load_new_theme (GtkFileSelection *selector, gpointer user_data);


void
on_new1_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
   free_all_memory();
   init_engine();
   destroy_board();
   init_game_board(main_window);
   load_values_from_file();

   //if ai is currently moving, notify that function that the user has 
   //decided to start a new game
   if (moving_ai)
      new_game = TRUE;
   what_next = WAIT_FOR_AI;
   while (move_ai());  //if both players are AI, keeps on running
}




void
on_quit1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

   state_hash = 0;
   gtk_main_quit();

}



void
on_clear1_activate                     (GtkMenuItem     *menuitem,
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
    GError *error = NULL;
    if (gnome_help_display("gamazons",NULL,&error))
      {
#ifdef DEBUG
       printf("I should pop up the help display now\n");
#endif
      }
    else
      {
#ifdef DEBUG
       printf("I couldn't display the help screen, sorry.\n");
#endif
       printf("%s\n", error->message );
      }
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
   int temp;
   GtkWidget *undo_button;
   int i;

   if (what_next == FIRE_ARROW) //Undo during mid-move
     {
      int to_col, from_col, to_row, from_row;

      temp = board->from;
      board->from = board->to;
      board->to = temp;

      try_move(board, board->selected_queen);

      //roll back the state of the board
      from_col = get_x_int_from_square(board->from);
      from_row = get_y_int_from_square(board->from);

      to_col = get_x_int_from_square(board->to);
      to_row = get_y_int_from_square(board->to);

      board->squares[to_row][to_col] = board->squares[from_row][from_col];
      board->squares[from_row][from_col] = NOTHING;
      gen_legal_moves(board->to); 

      if (board->squares[to_row][to_col] == WHITE)
	{
	 what_next = MOVE_WHITE_QUEEN;
	 for (i=0; i<4; i++) //update queen to square mapping
	   {
	    if (board->square_to_wh_queen_map[i] == to_row*10 + to_col)
	      {
	       board->square_to_wh_queen_map[i] = from_row*10 + from_col;
	       break;
	      }
	   }
	 update_status_bar();
	}
      else
	{
	 what_next = MOVE_BLACK_QUEEN;
	 for (i=0; i<4; i++) //update queen to square mapping
	   {
	    if (board->square_to_bl_queen_map[i] == to_row*10 + to_col)
	      {
	       board->square_to_bl_queen_map[i] = from_row*10 + from_col;
	       break;
	      }
	   }
	 update_status_bar();
	}

      undo_button = (GtkWidget *) lookup_widget(main_window, "BT_UNDO");
      gtk_widget_set_sensitive (undo_button, FALSE);
     }


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

/*==============================================================================
 * on_BT_AUTOFINISH_clicked               
 *
 * This starts the auto-finish process if allowed.  This can't be done inbetween
 * a human player moving & firing an arrow, or while an AI is moving.
 *
 * XXX In a perfect world, the autofinish button would be grayed out when it 
 * can't be used.  That way the human knows why on earth the !@#$ button isn't 
 * doing anything ;)
 */
void
on_BT_AUTOFINISH_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
   //if (allow_auto_finish && !moving_ai)
     //{
      options.white_player = AI;
      options.black_player = AI;
      options.engine.timeout = 1;
      options.engine.maxwidth = 15;
      while (move_ai());  //if both players are AI, keeps on running
     //}

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
   int i,j,k;
   GtkWidget *auto_button, *undo_button;

   //printf("MainEvent = %d\n", event);
   /* Does this do anything?
   if (data) {
      item = board->db_image [GPOINTER_TO_INT (data)];
      if (item == NULL && event->type != GDK_BUTTON_RELEASE) 
	 return 0;
   }
   */

   switch (event->type) {
       case GDK_BUTTON_PRESS:
	   if (event->button.button != 1)
	      break;	

#ifdef DEBUG
	   printf("what_next = %d\n", what_next);
#endif
	   board->orig_x = board->curr_x = event->button.x;
	   board->orig_y = board->curr_y = event->button.y;
	   from = get_square (board->curr_x, board->curr_y);
	   from_col = get_x_int_from_square(from);
	   from_row = get_y_int_from_square(from);

#ifdef DEBUG
	   print_board();
#endif

	   //Make sure it's time to move a queen before letting the user do it,
	   //as well as make sure he's moving his own queen.  Also make sure it's
   	   //a human's turn!
#ifdef DEBUG
	   printf("checking row %d, col %d\n", from_row, from_col);
	   square_contains(from);
	   printf("board->squares = %d\n",board->squares[from_row][from_col]);
#endif
	   if ((board->squares[from_row][from_col] == WHITE && 
		       what_next == MOVE_WHITE_QUEEN && 
		       options.white_player == HUMAN) ||
	       (board->squares[from_row][from_col] == BLACK && 
			what_next == MOVE_BLACK_QUEEN && 
			options.black_player == HUMAN))
	     {
	      //Human is moving a queen
#ifdef DEBUG
	      printf("board->squares = %d, what_next = %d\n", board->squares[from_row][from_col], what_next);
#endif
	      grabbed_queen = TRUE;
	      gen_legal_moves(from);
#ifdef DEBUG
	      printf("grabbing queen\n");
#endif
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
#ifdef DEBUG
	   printf("GDK_BUTTON_PRESS: board->to = %d  board->from = %d\n", board->to, board->from);
#endif
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
#ifdef DEBUG
	   printf("what_next = %d\n", what_next);
#endif
	   if (grabbed_queen == FALSE)
	      break;
	   else
	      grabbed_queen = FALSE;

	   if (item != NULL)
	      gnome_canvas_item_ungrab (item, event->button.time);


#ifdef DEBUG
	   printf("GDK_BUTTON_RELEASE: board->to = %d  board->from = %d\n", board->to, board->from);
#endif
	   drop_x = event->button.x;
	   drop_y = event->button.y;

	   //something funny here?
	   if (is_queen_square(get_square (drop_x, drop_y)))
	     {
	      try_move (board, item);
	      break;
	     }

#ifdef DEBUG
	   printf("Queen is dropped at coords %f, %f\n", drop_x, drop_y);
#endif
	   board->to = get_square (drop_x, drop_y);
#ifdef DEBUG
	   printf("new square is %d\n", board->to);
#endif
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
#ifdef DEBUG
	   printf("setting square %d%d to hold %d\n", to_row, to_col, board->squares[from_row][from_col]);
#endif

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
		 update_status_bar();

  	         auto_button = (GtkWidget *) lookup_widget(main_window, "BT_AUTOFINISH");
		 gtk_widget_set_sensitive (auto_button, FALSE);
  	         undo_button = (GtkWidget *) lookup_widget(main_window, "BT_UNDO");
		 gtk_widget_set_sensitive (undo_button, TRUE);

		 board->squares[to_row][to_col] = board->squares[from_row][from_col];
		 for (k=0; k<4; k++) //update square to queen mapping
		   {
		    if (board->square_to_wh_queen_map[k] == from_row*10 + from_col)
		      {
		       board->square_to_wh_queen_map[k] = to_row*10 + to_col;
		       break;
		      }
		    if (board->square_to_bl_queen_map[k] == from_row*10 + from_col)
		      {
		       board->square_to_bl_queen_map[k] = to_row*10 + to_col;
		       break;
		      }
		   }
		 board->squares[from_row][from_col] = NOTHING;
		 gen_legal_moves(board->to); //prepare moves for arrow
		}
	     }

#ifdef DEBUG
	   square_contains(board->to);
	   square_contains(board->from);
#endif


	   try_move (board, item);
	   /*
	   if (board->selected)
	      clear_square (&board->selected);
	      */
#ifdef DEBUG
	   printf("what_next = %d\n", what_next);
#endif
	   break;
       //default:
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
   GtkWidget *auto_button, *undo_button;

   count_queens();
   switch (event->type) 
     {
       case GDK_BUTTON_PRESS:
	   if (event->button.button != 1)
	      break;	
	   if (what_next != FIRE_ARROW)
	      break;

	   x_coord = event->button.x-4;
	   y_coord = event->button.y-4;

	   sq = get_square(x_coord, y_coord);
	   if (!is_move_legal(sq))
	      break;

	   /* Make sure the square is empty first */
	   col = get_x_int_from_square(sq);
	   row = get_y_int_from_square(sq);

#ifdef DEBUG
	   printf("what_next = %d\n", what_next);
	   printf("arrow fire:  ");
	   square_contains(sq);
#endif
	   if (board->squares[row][col] != NOTHING)
	      break;

	   fire_arrow(sq);
	   s = states.s[states.current_state];
	   register_move_with_engine(sq);

	   if (s->turn == WHITE_PLAYER)
	     {
	      what_next = MOVE_WHITE_QUEEN;
	      update_status_bar();
#ifdef DEBUG
	      printf("white moves next\n");
#endif
	     }
	   else if (s->turn == BLACK_PLAYER)
	     {
	      what_next = MOVE_BLACK_QUEEN;
	      update_status_bar();
#ifdef DEBUG
	      printf("black moves next\n");
#endif
	     }
	   else
	      printf("XXXXXXXXXXXXXXX  BLARGH!  I don't know who's turn it is!\n");


  	   auto_button = (GtkWidget *) lookup_widget(main_window, "BT_AUTOFINISH");
	   gtk_widget_set_sensitive (auto_button, TRUE);
  	   undo_button = (GtkWidget *) lookup_widget(main_window, "BT_UNDO");
	   gtk_widget_set_sensitive (undo_button, FALSE);
	   
	   //check for gameover
	   if (game_over(movelist))
	      break;

	   dup_state(s, states.s[++(states.current_state)]);
	   move_ai();
       //default:
     }

   return 0;

}

void
on_PlayerOKButton_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
   GtkWidget *time, *width, *depth;
   GtkWidget *white_ai, *white_h, *black_ai, *black_h;

   load_values_from_file();

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
   //if the ai is already moving, don't muck things up by calling it again.
   if (moving_ai == FALSE)
      while(move_ai());

}


void
on_PlayerCancelButton_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
   gtk_widget_destroy(PlayerSettingsWindow);

}


void
on_theme1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

   file_selector = gtk_file_selection_new ("Pick your theme file.");
   
   gtk_file_selection_set_filename (GTK_FILE_SELECTION (file_selector), PACKAGE_DATA_DIR "/gamazons/");
   gtk_file_selection_complete (GTK_FILE_SELECTION (file_selector), "*.theme");
   g_signal_connect (GTK_OBJECT (GTK_FILE_SELECTION (file_selector)->ok_button),
                     "clicked",
                     G_CALLBACK (load_new_theme),
                     NULL);
   			   
   /* Ensure that the dialog box is destroyed when the user clicks a button. */
   
   g_signal_connect_swapped (GTK_OBJECT (GTK_FILE_SELECTION (file_selector)->ok_button),
                             "clicked",
                             G_CALLBACK (gtk_widget_destroy), 
                             (gpointer) file_selector); 

   g_signal_connect_swapped (GTK_OBJECT (GTK_FILE_SELECTION (file_selector)->cancel_button),
                             "clicked",
                             G_CALLBACK (gtk_widget_destroy),
                             (gpointer) file_selector); 
   
   /* Display that dialog */
   
   gtk_widget_show (file_selector);

   //selected_filename = gtk_file_selection_get_filename (GTK_FILE_SELECTION (file_selector));

}

static void load_new_theme (GtkFileSelection *selector, gpointer user_data)
{
   selected_filename = gtk_file_selection_get_filename (GTK_FILE_SELECTION (file_selector));
   load_values_from_file(); //Get current settings
   load_images_from_theme (selected_filename); //load new theme settings
   store_values_in_file();  //store new settings
   destroy_board();
   draw_board();
   
}
