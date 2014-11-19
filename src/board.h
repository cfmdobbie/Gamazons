/* Definitions */

/* Widget Names */
#define BOARD_NAME "CNVS_GAMEBOARD"

/* the board size */
#define BOARD_SIZE 10
/* border around the board itself */
#define BOARD_BORDER 15
/* cell size on the board */
#define CELL_SIZE 40.0 
/* cell padding */
#define CELL_PAD 6.0
/* square colors */
#define SQUARE_COLOR_1 "white"
#define SQUARE_COLOR_2 "grey"

#define THICKNESS 3.0
#define QUEEN_OFFSET 15.0

/* Data structures */
typedef gushort Square;
typedef gchar   Piece;


#define TYPE_POSITION	       (position_get_type ())
#define POSITION(obj)          GTK_CHECK_CAST (obj, TYPE_POSITION, Position)
#define POSITION_CLASS(klass)  GTK_CHECK_CLASS_CAST (klass, TYPE_POSITION, PositionClass)
#define IS_POSITION(obj)       GTK_CHECK_TYPE (obj, TYPE_POSITION)

typedef struct _Position        Position;
typedef struct _PositionClass   PositionClass;
typedef struct _PositionPrivate PositionPrivate;

struct _PositionClass {
	GtkObjectClass parent_class;
};

struct _Position {
	GtkObject        object;

	/* 10x10 board - extra for move generation */
	Piece            square[120]; 

	PositionPrivate *priv;
};

#define TYPE_BOARD			(board_get_type ())
#define BOARD(obj)			(GTK_CHECK_CAST ((obj), TYPE_BOARD, Board))
#define BOARD_CLASS(klass)		(GTK_CHECK_CLASS_CAST ((klass), TYPE_BOARD, BoardClass))
#define IS_BOARD(obj)			(GTK_CHECK_TYPE ((obj), TYPE_BOARD))
#define IS_BOARD_CLASS(klass)		(GTK_CHECK_CLASS_TYPE ((obj), TYPE_BOARD))


struct amazon_board {
   Square squares[BOARD_SIZE][BOARD_SIZE];
   Square from;
   Square to;
   Square selected_from;
   GnomeCanvasItem *selected;
   GnomeCanvasItem *selected_queen;
   GnomeCanvasItem *white_queens[4];
   GnomeCanvasItem *black_queens[4];

   double orig_x;
   double orig_y;
   double curr_x;
   double curr_y;

   char db[120];
   GnomeCanvasItem *db_image[120];
   GnomeCanvasItem *square_items[100];
   GnomeCanvas *canvas;

   Position *pos;

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
};

/* Prototypes */

void init_game_board(GtkWidget *GamazonsMain);
void draw_board();
void mark_square (GnomeCanvasItem *square);


Square get_square (double x, double y);
void clear_square (GnomeCanvasItem **square);
void try_move (Board *board, GnomeCanvasItem *item);

void move_piece(move m);
int move_ai();
void register_move_with_engine(Square arrow_sq);
void gen_legal_moves(Square sq);
int is_move_legal(Square sq);
int is_queen_square(Square sq);
void free_all_memory();
int create_hash(state *s);


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

void draw_a_line(GnomeCanvasGroup *group, 
	int x1, int y1, int x2, int y2, char *color);

void fire_arrow(Square sq);
void square_contains(Square sq);
void count_queens();

