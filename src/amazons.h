#define ushort unsigned short
#define uchar unsigned char
#define ull unsigned long long
#define ulong unsigned long

#define TT 0x3d0925
#define MAX_TT_SEARCH 30

#define TRUE 1
#define FALSE 0

#define WHITE_PLAYER 1  //player 1
#define BLACK_PLAYER 2  //player 2

#define NOTHINK 0
#define THINK   1

#define GAMAZONS

//#define DEBUG_HEVAL 
//#define DEBUG_WEB

struct move_s
{
    uchar queen;
    uchar tocol, torow;
    uchar wallcol, wallrow;
    int val;
    int depth;
};
typedef struct move_s move;


//Basic game state at one point in time
struct state_s
{
    ull white_bd[2];
    ull black_bd[2];
    ull blocks_bd[2];

    uchar white_q_x[4];       
    uchar white_q_y[4];       

    uchar black_q_x[4];
    uchar black_q_y[4];

    uchar turn;
    short value;
    uchar depth;
    uchar winner;
};

//state stored in the transposition table
struct state_t
{
    ull white_bd[2];
    ull black_bd[2];
    ull blocks_bd[2];

    uchar turn;
    uchar depth;
    short value;
    short alpha;
    short beta;
};

typedef struct state_s state;
typedef struct state_t state_t;
state_t **tt;

//Collection of all game states
struct game_states 
{
   state *s[100];
   int current_state;
   int max_state;
};


//Global game options
struct engine 
{
   int timeout;
   int maxdepth;
   int maxwidth;
};

struct options
{
   int white_player;
   int black_player;
   int print_statistics;

   struct engine engine;

};

// Different player choices
enum {
   AI,
   HUMAN,
};

/* intersting statistic globals */
int tt_overwrite;
int tt_stores;

int tt_updates;
int tt_lookups;
int tt_lookup_finds;
int heval_calls;



/* Prototypes */
int sean_heval(state *s);
move savemove(state *s, move m);
int mmselect(int oldval, int newval);
int test(state *s, uchar col, uchar row);
int xor(ull bd[2], uchar col, uchar row);
int pboard(state);
move search(state *s, int depth, int alpha, int beta, int, int);
move isearch(state *s, int);
move getmove(state *s, int player);
int pvec(ull v);
int moves(ushort q[][13], int w);
int minmoves(ushort q[][13], int w);
int maxmoves(ushort q[][13], int w);
int countmoves(ushort q[][13], int w);
int pbits(ushort q[][13], int s);
int children(state *s, move movelist[]);
int countchildren(state *s);
int undomove(state *s, move m);
char get_token();
void clear_buf();
int move_lookup(move *m, move movelist[], int move_count);
void dup_state(state *s_old, state *s_new);
#ifdef GAMAZONS
int engine_init();
void load_values_from_file();
void store_values_in_file();

#endif


int makemove(state *s, move m);
void print_usage_menu();
void parse_args(int argc, char *argv[]);
void print_stats();

/* eval.c */
int get_forward_diag(ull board_l, ull board_u, int diag);
int get_back_diag(ull board_l, ull board_u, int diag);
void put_forward_diag(ull *board_l, ull *board_u, ushort stream, int diag);
void put_back_diag(ull *board_l, ull *board_u, ushort stream, int diag);
int calc_stream_moves(ushort stream, ushort pos, ushort len);
int calc_moves(ull board_l, ull board_u, int pos);
int count_contig_bits(ushort stream, int len);
int heval(state *s);
ushort gen_web_stream(ushort stream, int pos, int len);
ushort gen_web_stream_plus(ushort stream, int pos, int len);
void gen_web_board(ull *web_l, ull *web_u, ull board_l, ull board_u, int pos);
int gen_web_board_count(ull *web_l, ull *web_u, ull board_l, ull board_u, int pos);
void gen_dirs_board(ull *board_l, ull *board_u, int pos);
int count_bits(ull board_l, ull board_u);



int pbvec(ull l, ull u);

state_t *tt_lookup(state *s);
void tt_store(state *s, short alpha, short beta);
void tt_update(state *s, short alpha, short beta);

int tt_compare(state *s, state_t *t);




//convert x,y coords to pos 0-99
#define XY_TO_POS(x,y) y*10 + x

/* Bit board stuff */
#define GET_ROW(board, row) (board >> (row%5) * 10) & 0x3ff
#define GET_COL(board_l, board_u, col) (GET_HALF_COL(board_l, col) | (GET_HALF_COL(board_u, col) << 5)) 

#define GET_HALF_COL(board, col) (((board >> col) &0x1) | ((board >> (col + 9)) &0x2) | ((board >> (col + 18)) &0x4) | ((board >> (col + 27)) &0x8) | ((board >> (col + 36)) &0x10))

/* These defines require a board number between 0-99 */
//Tells you where in a stream of 10 bits the position (x,y) would be (0-9)
#define GET_COL_POS(y) (int) y / 10
#define GET_ROW_POS(x) x % 10
//Tells you where in a stream of up to 10 bits the position (f,b) would be (0-9)
#define GET_FDIAG_POS(f) (f%10 > f/10) ? f/10 : f%10
#define GET_BDIAG_POS(b) (b/10 < (10 - b%10)) ? b/10 : 9 - b%10

//Gets diag numbers, for passing into get_forw_diag() & get_back_diag()
#define GET_FDIAG(f) (f%10 > f/10) ? f - ((f/10) * 11) : f - ((f%10) * 11)
#define GET_BDIAG(b) (b/10 < (10 - b%10)) ? b - ((b/10) * 9) : b - ((9 - (b%10)) * 9)

//Calculates length of a diagonal, pass in value from GET_FDIAG/GET_BDIAG
//Note: Don't call GET_[F,B]DIAG within GET_[F,B]DIAG_LEN, you get really weird results
//eg GET_FDIAG_LEN(GET_FDIAG(pos)).  Instead, store it into a variable first:
//eg diag = GET_FDIAG(pos); len = GET_FDIAG_LEN(diag);
#define GET_FDIAG_LEN(fdiag) (fdiag < 10) ? (10 - fdiag) : (10 - fdiag/10)
#define GET_BDIAG_LEN(bdiag) (bdiag < 10) ? bdiag + 1 : (10 - bdiag/10)

#define PUT_ROW(board, row, stream) board |= ((ull) stream << ((row % 5) * 10))
#define PUT_COL(board_l, board_u, col, stream) PUT_HALF_COL(board_l, col, stream); PUT_HALF_COL(board_u, col, stream >> 5)
#define PUT_HALF_COL(board, col, stream) board |= ((((ull)stream & 0x1) << col) | \
					 (((ull)stream & 0x2) << (col + 9)) | \
					 (((ull)stream & 0x4) << (col + 18)) | \
					 (((ull)stream & 0x8) << (col + 27)) | \
					 (((ull)stream & 0x10) << (col + 36)))
