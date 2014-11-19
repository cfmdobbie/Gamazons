/* Definitions */

/* Widget Names */
#define BOARD_NAME "CNVS_GAMEBOARD"

/* the board size */
#define BOARD_SIZE 10
/* border around the board itself */
#define BOARD_BORDER 0
/* cell size on the board */
#define CELL_SIZE 40.0 
/* cell padding */
#define CELL_PAD 6.0
/* square colors */
#define SQUARE_COLOR_1 "white"
#define SQUARE_COLOR_2 "grey"

#define THICKNESS 1.0
#define QUEEN_OFFSET 0

#define INVALID_SQUARE_VALUE 101

/* Data structures */
typedef gushort Square;
typedef gchar   Piece;


struct amazon_board {

   // Gnome canvas counts coordinates w/ origin starting in top/left corner
   Square squares[BOARD_SIZE][BOARD_SIZE];
   //These are really meant for temporary processing, and might not contain
   //safe values.  They are currently candidates for downsizing.
   //Square from;
   //Square to;

   /* The AI engine queens were managed in an array w/ elements 0-3
    * this mapping is meant to keep track of which queen is on which
    * square 
    */
   Square square_to_wh_queen_map[4];
   Square square_to_bl_queen_map[4];

   GnomeCanvasItem *selected_queen;
   GnomeCanvasItem *white_queens[4];
   GnomeCanvasItem *black_queens[4];

   double orig_x;
   double orig_y;
   double curr_x;
   double curr_y;

   char db[120];
   GnomeCanvasItem *square_items[100];
   GnomeCanvasGroup *root;
   GnomeCanvas *canvas;


};
typedef struct amazon_board Board;


/* Possible square occupants */
enum {
   NOTHING,
   BLACK,
   WHITE,
   ARROW
};

//GUI states
enum {
   FIRE_ARROW,
   MOVE_BLACK_QUEEN,
   MOVE_WHITE_QUEEN,
   WAIT_FOR_AI,
   UNDO,
   AUTO_FINISH,
   FORCE_MOVE,
   START_GAME,
   NEW_GAME,
   LOAD_GAME,
   START_REPLAY,
   STOP_REPLAY,
   GAME_OVER,
   QUIT_GAME,
   CONFUSED
};

/* Prototypes */

void init_game_board(GtkWidget *GamazonsMain);
void draw_board();
void mark_square (GnomeCanvasItem *square);


Square get_square (double x, double y);
void clear_square (GnomeCanvasItem **square);
//void try_move (Board *board, GnomeCanvasItem *item);
void move_piece_to (Square to, GnomeCanvasItem *item);

void move_piece(move m);
int move_ai();
void register_move_with_engine(Square arrow_sq);
void gen_legal_moves(Square sq);
int is_move_legal(Square sq);
int is_queen_square(Square sq);
void free_all_memory();
int create_hash(state *s);
void print_board();
void destroy_board();
void print_move_in_text_window(move *m);
int read_in_moves(FILE *history_fd);
void get_move_str(move *m, char move_str[]);
int get_move_from_str(move *m, char move_str[]);
void rest(int duration);


// Coordinate conversion routines
double get_x_from_square(int sq);
double get_y_from_square(int sq);
int get_x_int_from_square(int sq);
int get_y_int_from_square(int sq);
int engine_x_to_board_x(int eng_x);
int engine_y_to_board_y(int eng_y);
int board_x_to_engine_x(int brd_x);
int board_y_to_engine_y(int brd_y);
int get_square_from_engine(int x, int y);


void fire_arrow(Square sq);
void square_contains(Square sq);
void count_queens();
int game_over();


