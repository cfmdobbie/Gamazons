/*************

sean mcmillen
ronald yorgason

CS410 Combinatorial Games -- Spring 2002

amazons player. 

amazons -h for options

Project URL:     http://www.yorgalily.org/amazons/

***************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <assert.h>
#include <ctype.h>
#include <sys/poll.h>

#ifdef GAMAZONS
#include <gnome.h>
#endif

#include "amazons.h"
#include "unit-test.h"


#define HEVAL heval  // for testing differant hevals
#define MINDEPTH 1
#define VERBOSE 0
#define TIMED 1      // boolean, if 1 then TIMEOUT is in effect, if 0 then no

// macros

#define MIN(a,b)    (a < b ? a : b)
#define MAX(a,b)    (a > b ? a : b)
#define MMSET(p,q)    ((p) == 1 ? SHRT_MIN+q : SHRT_MAX-q)

// constants

#define WHITEQUEENS 4
#define BLACKQUEENS 4

/* local prototypes */
move mtdf(state *s, int guess, int tdepth);


// some globals //
FILE *movin;                        // read moves from here
FILE *movout;                       // write moves to here
struct pollfd pollstruct;           // used to poll FILE *movin

int onmove;
int nodes;                        // statitics gatherer
int rawnodes;                     // statitics gatherer
int hevalz;                        // statitics gatherer
int hits;                        // statitics gatherer
int ok;                            // global, if 0 then timeout condition 
time_t start;                    // global, start of search, used for timeout
                                // check
struct options options;
struct game_states states;

#ifdef GAMAZONS
extern int state_hash;
#endif

// command line flags -- set defaults here
/*
int white_player = FALSE;
int black_player = FALSE;
int print_statistics = FALSE;
int TIMEOUT = 5;
int MAXDEPTH = 20;
int MAXWIDTH = 5000;
 */

int obst_heval(state *s)
{
   int moves;

   int t1;
   int t2;
   int turn;

   if (onmove > 10)
      return heval(s);

   turn = s->turn;

   s->turn = WHITE_PLAYER;

   t1 =  countobst(s);

   s->turn = BLACK_PLAYER;

   t2 =  countobst(s);

   s->turn = turn;

   moves = t1 - t2;
   return moves;
}






int countobst(state *s)
{
   int i,j;
   int m=0, p=0;
   int xo=0, yo=0;
   int axo=0, ayo=0;
   int dir, adir;
   int QUEENS;

   uchar *queens_x;
   uchar *queens_y;
   ull *board;

   int queen = 0;

   if(s->turn == WHITE_PLAYER)
     {
      queens_x = s->white_q_x;
      queens_y = s->white_q_y;
      board = s->white_bd;
      QUEENS = WHITEQUEENS;
     }
   else
     {
      queens_x = s->black_q_x;
      queens_y = s->black_q_y;
      board = s->black_bd;
      QUEENS = BLACKQUEENS;
     }

   // order: N NE E SE S SW W NW 
   for (queen = 0; queen < QUEENS; queen++)
     {
      for (dir = 0; dir < 8; dir++)
       	{
	 // for tightness not speed
	 switch (dir)
	   {
	     case 0:
		 xo = 0; yo = 1;
		 break;
	     case 1:
		 xo = 1; yo = 1;
		 break;
	     case 2:
		 xo = 1; yo = 0;
		 break;
	     case 3:
		 xo = 1; yo = -1;
		 break;
	     case 4: 
		 xo = 0; yo = -1;
		 break;
	     case 5:
		 xo = -1; yo = -1;
		 break;
	     case 6:
		 xo = -1; yo = 0;
		 break;
	     case 7: 
		 xo = -1; yo = 1;
		 break;
	   }

	 for (i=1; i < 10; i++) 
	   {
	    // out of bounds
	    if (queens_x[queen] + xo*i > 9 ||
		    queens_y[queen] + yo*i > 9 ||
		    queens_x[queen] + xo*i < 0 ||
		    queens_y[queen] + yo*i < 0)
	      {
	       // count obst
	       for (adir = 0; adir < 8; adir++)
		 {
		  // for tightness not speed
		  switch (adir)
		    {
		      case 0:
			  axo = 0; ayo = 1;
			  break;
		      case 1:
			  axo = 1; ayo = 1;
			  break;
		      case 2:
			  axo = 1; ayo = 0;
			  break;
		      case 3:
			  axo = 1; ayo = -1;
			  break;
		      case 4: 
			  axo = 0; ayo = -1;
			  break;
		      case 5:
			  axo = -1; ayo = -1;
			  break;
		      case 6:
			  axo = -1; ayo = 0;
			  break;
		      case 7: 
			  axo = -1; ayo = 1;
			  break;
		    }
		  if (dir == adir) continue;

		  for (j=1; j < 2; j++) 
		    {
		     if (queens_x[queen] + axo*j > 9 ||
			     queens_y[queen] + ayo*j > 9 ||
			     queens_x[queen] + axo*j < 0 ||
			     queens_y[queen] + ayo*j < 0)
		       {
		       	break;
		       }

		     if (test(s, queens_x[queen]+axo*j, 
				 queens_y[queen]+ayo*j))
		       {
		       	break;
		       }
		     m+=1;
		    }
		 }
	       break;
	      }

	    // hit a wall
	    if (test(s, queens_x[queen]+xo*i, queens_y[queen]+yo*i))
	      {
	       for (adir = 0; adir < 8; adir++)
		 {
		  // for tightness not speed
		  switch (adir)
		    {
		      case 0:
			  axo = 0; ayo = 1;
			  break;
		      case 1:
			  axo = 1; ayo = 1;
			  break;
		      case 2:
			  axo = 1; ayo = 0;
			  break;
		      case 3:
			  axo = 1; ayo = -1;
			  break;
		      case 4: 
			  axo = 0; ayo = -1;
			  break;
		      case 5:
			  axo = -1; ayo = -1;
			  break;
		      case 6:
			  axo = -1; ayo = 0;
			  break;
		      case 7: 
			  axo = -1; ayo = 1;
			  break;
		    }
		  //if (dir == adir) continue;
		  if (dir == adir) continue;

		  for (j=1; j < 2; j++) 
		    {
		     if (queens_x[queen] + axo*j > 9 ||
			     queens_y[queen] + ayo*j > 9 ||
			     queens_x[queen] + axo*j < 0 ||
			     queens_y[queen] + ayo*j < 0)
		       {
		       	break;
		       }

		     if (test(s, queens_x[queen]+axo*j, 
				 queens_y[queen]+ayo*j))
		       {
		       	break;
		       }
		     m+=1;
		    }
		 }
	       break;
	      }

	    m+=2;
	    /*
	       xor(board, queens_x[queen], queens_y[queen]);
	       queens_x[queen] += i*xo;
	       queens_y[queen] += i*yo;
	       xor(board, queens_x[queen], queens_y[queen]);

	    // look for arrow moves.
	    // order: N NE E SE S SW W NW 
	    xor(board, queens_x[queen], queens_y[queen]);
	    queens_x[queen] -= i*xo;
	    queens_y[queen] -= i*yo;
	    xor(board, queens_x[queen], queens_y[queen]);
	     */
	   }
       	}
     }
   return m;
}

// heuristic function
int sean_heval(state *s)
{
   int moves;

   int t1;
   int t2;
   int turn;

   turn = s->turn;

   s->turn = WHITE_PLAYER;

   t1 =  countchildren(s);

   s->turn = BLACK_PLAYER;

   t2 =  countchildren(s);

   s->turn = turn;

   moves = t1 - t2;
   return moves;
}

int countchildren(state *s)
{
   int i,j;
   int m=0;
   int xo=0, yo=0;
   int axo=0, ayo=0;
   int dir, adir;
   int QUEENS;

   uchar *queens_x;
   uchar *queens_y;
   ull *board;

   int queen = 0;

   if(s->turn == WHITE_PLAYER)
     {
      queens_x = s->white_q_x;
      queens_y = s->white_q_y;
      board = s->white_bd;
      QUEENS = WHITEQUEENS;
     }
   else
     {
      queens_x = s->black_q_x;
      queens_y = s->black_q_y;
      board = s->black_bd;
      QUEENS = BLACKQUEENS;
     }

   // look for moves.
   // order: N NE E SE S SW W NW

   // this loop moves a queen, shoots an arrow, all the while 
   // checking to see if its run into things. 
   // populated movelist (passing in as reference) with the valid moves.
   for (queen = 0; queen < QUEENS; queen++)
     {
      for (dir = 0; dir < 8; dir++)
       	{
	 // for tightness not speed
	 switch (dir)
	   {
	     case 0:
		 xo = 0; yo = 1;
		 break;
	     case 1:
		 xo = 1; yo = 1;
		 break;
	     case 2:
		 xo = 1; yo = 0;
		 break;
	     case 3:
		 xo = 1; yo = -1;
		 break;
	     case 4: 
		 xo = 0; yo = -1;
		 break;
	     case 5:
		 xo = -1; yo = -1;
		 break;
	     case 6:
		 xo = -1; yo = 0;
		 break;
	     case 7: 
		 xo = -1; yo = 1;
		 break;
	   }

	 for (i=1; i < 10; i++) 
	   {
	    // out of bounds
	    if (queens_x[queen] + xo*i > 9 ||
		    queens_y[queen] + yo*i > 9 ||
		    queens_x[queen] + xo*i < 0 ||
		    queens_y[queen] + yo*i < 0)
	      {
	       break;
	      }

	    // hit a wall
	    if (test(s, queens_x[queen]+xo*i, queens_y[queen]+yo*i))
	      {
	       break;
	      }

	    xor(board, queens_x[queen], queens_y[queen]);
	    queens_x[queen] += i*xo;
	    queens_y[queen] += i*yo;
	    xor(board, queens_x[queen], queens_y[queen]);

	    // look for arrow moves.
	    // order: N NE E SE S SW W NW 
	    for (adir = 0; adir < 8; adir++)
	      {
	       // for tightness not speed
	       switch (adir)
		 {
		   case 0:
		       axo = 0; ayo = 1;
		       break;
		   case 1:
		       axo = 1; ayo = 1;
		       break;
		   case 2:
		       axo = 1; ayo = 0;
		       break;
		   case 3:
		       axo = 1; ayo = -1;
		       break;
		   case 4: 
		       axo = 0; ayo = -1;
		       break;
		   case 5:
		       axo = -1; ayo = -1;
		       break;
		   case 6:
		       axo = -1; ayo = 0;
		       break;
		   case 7: 
		       axo = -1; ayo = 1;
		       break;
		 }

	       for (j=1; j < 10; j++) 
		 {
		  if (queens_x[queen] + axo*j > 9 ||
			  queens_y[queen] + ayo*j > 9 ||
			  queens_x[queen] + axo*j < 0 ||
			  queens_y[queen] + ayo*j < 0)
		    {
		     break;
		    }

		  if (test(s, queens_x[queen]+axo*j, 
			      queens_y[queen]+ayo*j))
		    {
		     break;
		    }

		  // put arrow
		  m++;
		 }
	      }
	    xor(board, queens_x[queen], queens_y[queen]);
	    queens_x[queen] -= i*xo;
	    queens_y[queen] -= i*yo;
	    xor(board, queens_x[queen], queens_y[queen]);
	   }
       	}
     }
   return m;
}

// populates movelist[] with all possible moves.
// returns the count of moves
// the value of the move is also set here, that means 
// this is the function that calls heval (heuristic) 
//  and tt_lookup (transposition table retrieve)

int children(state *s, move movelist[])
{
   int i,j;
   int m=0;
   int xo=0, yo=0;
   int axo=0, ayo=0;
   int dir, adir;
   int QUEENS;

   uchar *queens_x;
   uchar *queens_y;
   ull *board;

   int queen = 0;

   if(s->turn == WHITE_PLAYER)
     {
      queens_x = s->white_q_x;
      queens_y = s->white_q_y;
      board = s->white_bd;
      QUEENS = WHITEQUEENS;
     }
   else
     {
      queens_x = s->black_q_x;
      queens_y = s->black_q_y;
      board = s->black_bd;
      QUEENS = BLACKQUEENS;
     }

   // look for moves.
   // order: N NE E SE S SW W NW

   // this loop moves a queen, shoots an arrow, all the while 
   // checking to see if its run into things. 
   // populated movelist (passing in as reference) with the valid moves.
   for (queen = 0; queen < QUEENS; queen++)
     {
      for (dir = 0; dir < 8; dir++)
       	{
	 // for tightness not speed
	 switch (dir)
	   {
	     case 0:
		 xo = 0; yo = 1;
		 break;
	     case 1:
		 xo = 1; yo = 1;
		 break;
	     case 2:
		 xo = 1; yo = 0;
		 break;
	     case 3:
		 xo = 1; yo = -1;
		 break;
	     case 4: 
		 xo = 0; yo = -1;
		 break;
	     case 5:
		 xo = -1; yo = -1;
		 break;
	     case 6:
		 xo = -1; yo = 0;
		 break;
	     case 7: 
		 xo = -1; yo = 1;
		 break;
	   }

	 for (i=1; i < 10; i++) 
	   {
	    // out of bounds
	    if (queens_x[queen] + xo*i > 9 ||
		    queens_y[queen] + yo*i > 9 ||
		    queens_x[queen] + xo*i < 0 ||
		    queens_y[queen] + yo*i < 0)
	      {
	       break;
	      }

	    // hit a wall
	    if (test(s, queens_x[queen]+xo*i, queens_y[queen]+yo*i))
	      {
	       break;
	      }

	    xor(board, queens_x[queen], queens_y[queen]);
	    queens_x[queen] += i*xo;
	    queens_y[queen] += i*yo;
	    xor(board, queens_x[queen], queens_y[queen]);

	    // look for arrow moves.
	    // order: N NE E SE S SW W NW 
	    for (adir = 0; adir < 8; adir++)
	      {
	       // for tightness not speed
	       switch (adir)
		 {
		   case 0:
		       axo = 0; ayo = 1;
		       break;
		   case 1:
		       axo = 1; ayo = 1;
		       break;
		   case 2:
		       axo = 1; ayo = 0;
		       break;
		   case 3:
		       axo = 1; ayo = -1;
		       break;
		   case 4: 
		       axo = 0; ayo = -1;
		       break;
		   case 5:
		       axo = -1; ayo = -1;
		       break;
		   case 6:
		       axo = -1; ayo = 0;
		       break;
		   case 7: 
		       axo = -1; ayo = 1;
		       break;
		 }

	       for (j=1; j < 10; j++) 
		 {
		  if (queens_x[queen] + axo*j > 9 ||
			  queens_y[queen] + ayo*j > 9 ||
			  queens_x[queen] + axo*j < 0 ||
			  queens_y[queen] + ayo*j < 0)
		    {
		     break;
		    }

		  if (test(s, queens_x[queen]+axo*j, 
			      queens_y[queen]+ayo*j))
		    {
		     break;
		    }

		  /*
		  // put arrow
		  xor(s->blocks_bd, queens_x[queen]+axo*j, queens_y[queen]+ayo*j);
		  s->turn ^= 3;

		  //                        printf("evaluating board:");
		  //                        pboard(*s);
		  if ((stt = tt_lookup(s)))
		  {
		  //tt_yes++;
		  hits++;
		  movelist[m].val = stt->value;
		  movelist[m].depth = stt->depth;
		  }
		  else
		  {
		  //tt_no++;
		  movelist[m].val = HEVAL(s);
		  hevalz++;
		  s->value = movelist[m].val;
		  s->depth = 1;
		  tt_store(s, SHRT_MIN, SHRT_MAX);
		  }

		  // remove arrow
		  xor(s->blocks_bd, queens_x[queen]+axo*j, queens_y[queen]+ayo*j);
		  s->turn ^= 3;

		   */
		  movelist[m].queen=queen;
		  movelist[m].tocol=queens_x[queen];
		  movelist[m].torow=queens_y[queen];
		  movelist[m].wallcol=queens_x[queen]+axo*j;
		  movelist[m].wallrow=queens_y[queen]+ayo*j;

		  //                        pmove(movelist[m]);
		  //                        printf("\n");

		  m++;
		 }
	      }
	    xor(board, queens_x[queen], queens_y[queen]);
	    queens_x[queen] -= i*xo;
	    queens_y[queen] -= i*yo;
	    xor(board, queens_x[queen], queens_y[queen]);
	   }
       	}
     }
   return m;
}

// for qsort
int mincompare(move *m1, move *m2) // USED BY MAXIMIZER
{
   if (m1->val > m2->val)
      return -1;
   else if (m1->val < m2->val)
      return 1;
   return 0;
}

// for qsort
int maxcompare(move *m1, move *m2)
{
   if (m1->val < m2->val)
      return -1;
   else if (m1->val > m2->val)
      return 1;
   return 0;
}

// top level iterative search function. called from main, pretty
// self explanatory
move isearch(state *s, int think)
{
   int i;
   move temp1, temp2;
   move even, odd;

   even.val = 0;
   odd.val = 0;

   for (i=MINDEPTH; i <= options.engine.maxdepth; i++)
     {
      rawnodes = 0;
      nodes = 0;
      hits = 0;
      hevalz =0;


      temp1 = search(s, 0, SHRT_MIN, SHRT_MAX, i, think);

      /*

      // for mtdf NOT WORKING CURRENTLY
      if (i & 1)
      {
      temp1 = mtdf(s, odd.val, i);
      even = temp1;
      }
      else
      {
      temp1 = mtdf(s, even.val, i);
      odd = temp1;
      }
       */

      //printf("Searched to depth %d, %d cache hits of %d lookups. %d nodes searched.\n", i,hits,rawnodes, nodes);
      //printf("hevals = %d\n", hevalz);
      if (ok)          // using this global ok is pretty sloppy but works.
      	{
	 temp2 = temp1;
       	}
      else
       	{
	 if (think)
	   {
#ifdef DEBUG
	    printf("searched %d nodes on your time\n", nodes);
#endif
	   }
#ifdef DEBUG
	 printf("time's up at depth %d\n", i);
#endif
	 break;
       	}

     }
   return temp2;
}

// NOT WORKING
move mtdf(state *s, int guess, int tdepth)
{
   move temp;
   //int f;
   int lowerbound = SHRT_MIN;
   int upperbound = SHRT_MAX;
   int beta;

   temp.val = guess;

   do
     {
      if (temp.val == lowerbound)
       	{
	 beta = temp.val + 1;
       	}
      else
       	{
	 beta = temp.val;
       	}

      //temp = search(s, 0, beta - 1, beta, tdepth, think);

      if (temp.val < beta)
       	{
	 upperbound = temp.val;
       	}
      else
       	{
	 lowerbound = temp.val;
       	}
     }
   while (!(lowerbound >= upperbound));

   return temp;
}

// minimax search.
// tdepth is "target depth", that is the current iterative target level
move search(state *s, int depth, int alpha, int beta, int tdepth, int think)
{
   state_t *stt;
   move movelist[3000];
   int i;
   int index=0;
   move stemp;
   move temp;
   int randomizer;
   //    int tt_yes=0;
   //    int tt_no=0;

   int movecount;

   int done;

   nodes++;

   if ((time_t)time(NULL) - start > options.engine.timeout && TIMED && !think)
     {
      ok = 0;
      return movelist[0];
     }

   if (think)
     {
      if (poll(&pollstruct, 1, 0))
       	{
	 ok = 0;
	 return movelist[0];
       	}
     }

   movecount = children(s, movelist);

   if (movecount == 0) // no more moves
     {
      if (depth == 0)
       	{
#ifdef DEBUG
	 printf("player %d wins!\n", s->turn^3);
#endif
	 s->winner = s->turn^3;
	 if (options.print_statistics)
	    print_stats();
#ifndef GAMAZONS
	 exit(1);
#endif
       	}

      // if no more moves, then set the value here to 
      // a very high value plus/minus the depth
      // this ensure that the loser will select the longest path
      // to loss, and the winner will select the shortest path to
      // a win.
      movelist[0].val = MMSET(s->turn, depth);
     }

   // for node reordering, make sure everything has a value.
   for (i=0; i <movecount; i++)
     {

#ifdef GAMAZONS
      //Make the game responsive while the AI is thinking
      while (gtk_events_pending())
	 gtk_main_iteration();
#endif

      temp = savemove(s, movelist[i]);
      makemove(s, movelist[i]);
      if ((stt = tt_lookup(s)))
       	{
	 if (alpha >= stt->alpha && beta <= stt->beta) // correct
	   {
	    hits++;
	    movelist[i].val = stt->value;
	    movelist[i].depth = stt->depth;
	   }
	 else
	   {
	    movelist[i].val = HEVAL(s);
	    hevalz++;
	    s->value = movelist[i].val;
	    s->depth = 1;
	    tt_update(s, SHRT_MIN, SHRT_MAX);
	   }
       	}
      else
       	{
	 movelist[i].val = HEVAL(s);
	 hevalz++;
	 s->value = movelist[i].val;
	 s->depth = 1;
	 tt_store(s, SHRT_MIN, SHRT_MAX);
       	}
      undomove(s, temp);
     }

   rawnodes += movecount;

   // node reordering here.

   if (s->turn == WHITE_PLAYER)
      qsort(movelist, movecount, sizeof(move), (void*)mincompare);
   else
      qsort(movelist, movecount, sizeof(move), (void*)maxcompare);

   // this is the end of the line, return best move.
   if (depth+1 >= tdepth)
      return movelist[0];

   done = 0;
   for (i=0; i < movecount && !done && i < options.engine.maxdepth; i++)

     {
      // already searched farther than we will in the TT, just return it.
      if (movelist[i].depth > tdepth - depth)
	 return movelist[i];

      temp = savemove(s, movelist[i]);
      makemove(s, movelist[i]);

      stemp = search(s, depth+1, alpha, beta, tdepth, think);

      if (ok)
       	{
	 // this should perhaps check if tt_lookup still works 
	 // not life changing
	 if (tdepth-depth > movelist[i].depth)
	   {
	    s->value = stemp.val;
	    s->depth = tdepth-depth;
	    tt_update(s, alpha, beta);
	   }

	 movelist[i].val = stemp.val;
	 undomove(s,temp); // undo move.
      	}
      else // times up, return back up the tree as fast as possible.
      	{
	 undomove(s,temp); // undo move.
       	 return movelist[i];
       	}

      nodes++;

      // alpha-beta stuff:

      if (s->turn == WHITE_PLAYER) 
	{
	 if (movelist[i].val > alpha)
	   {
	    alpha = movelist[i].val;
	    index = i;
	   }
       	}
      else
       	{
	 if (movelist[i].val < beta)
	   {
	    beta = movelist[i].val;
	    index = i;
	   }
       	}

      if (alpha >= beta)
       	{
	 done = 1;
       	}
     }

   /* XXX
   printf("movelist index = %d\n", index);
   if (movecount > 3)
     {
      randomizer = rand() %3;
      printf("randomizer = %d\n", randomizer);
     }
     */

   return movelist[index];
}

// print out a longlong in binary
int pvec(ull v)
{
   int i;

   printf("->");
   for (i=49; i >= 0; i--)
     {
      printf("%d", (int)((v >> i) & (ull)1));
      if (i%10 == 0)
	 printf(" ");
     }
   printf("<-\n");

   return 0;
}

// bring out a nice representation of the playing board
int pboard(state s)
{
   int board[12][12];
   int i,j;
   int row, col;

   // make the whole board blanks
   for (i=0; i < 12; i++)
      for (j=0; j < 12; j++)
	 board[i][j] = '.';

   // place player1 queens
   for (i=0; i < WHITEQUEENS; i++)
     {
      col = s.white_q_x[i];
      row = s.white_q_y[i];
      if (options.white_player == HUMAN) board[col][row] = i+48;
      else board[col][row] = 'W';
     }

   // place player2 queens
   for (i=0; i < BLACKQUEENS; i++)
     {
      col = s.black_q_x[i];
      row = s.black_q_y[i];
      if (options.black_player == HUMAN) board[col][row] = i+48;
      else  board[col][row] = 'B';
     }

   // put walls on the board
   //pvec(s.blocks_bd[1]);
   for (i=0; i < 50; i++)
     {
      if ((s.blocks_bd[1] >> i) & 1)
       	{
	 board[i%10][i/10+5] = 'x';
       	}
     }
   //pvec(s.blocks_bd[0]);

   for (i=0; i < 50; i++)
     {
      if ((s.blocks_bd[0] >> i) & 1)
       	{
	 board[i%10][i/10] = 'x';
       	}
     }
   printf("\n");

   // print out the board
   for (i=9; i >= 0; i--)
     {
      printf("%2d ", i);
      for (j=0; j < 10; j++)
       	{
	 printf(" %c", board[j][i]);
       	}
      printf("\n");
     }

   printf("    a b c d e f g h i j\n");
   //printf("    0 1 2 3 4 5 6 7 8 9\n");
   printf("\n");
   return 0;
}

/*==============================================================================
 * getmove
 *
 * Gets the move coordinates from stdin.  Does lots of nice error checking on the
 * input, and makes sure the move was legal.  If no moves are available, the human
 * must have lost, so the game ends.
 */
move getmove(state *s, int player)
{
   char tok;
   int done = FALSE;
   move movelist[3000];
   int move_count;
   move m;
   char move_str[10];
   int i;

   move_count = children(s, movelist);
   if (move_count == 0)
     {
      printf("Ha ha ha, you lose SUCKER!\n");
      s->winner = s->turn^3;
#ifndef GAMAZONS
      exit(0);
#endif
     }

   do 
     {
      i = 0;

      printf("player %d's move.\n", player);
      printf("queen newcol newrow burncol burnrow (ex. \"0 c4 c1\")\n");
      printf("Move> ");
      fflush(stdout);

      ok = 1;
      isearch(s, THINK);

      tok = get_token();
      if (isdigit(tok))
       	{
	 m.queen = tok - '0';
	 move_str[i++] = tok;
	 move_str[i++] = ' ';
       	}
      else
       	{
	 printf("%c is not a valid queen\n\n", tok);
	 clear_buf();
	 continue;
       	}

      tok = get_token();
      if (isdigit(tok - '1')) //convert from alpha char to alpha num
       	{
	 m.tocol = tok - 'a';
	 move_str[i++] = tok;
       	}
      else
       	{
	 printf("%c is not a valid column\n\n", tok);
	 clear_buf();
	 continue;
       	}

      tok = get_token();
      if (isdigit(tok))
       	{
	 m.torow = tok - '0';
	 move_str[i++] = tok;
	 move_str[i++] = ' ';
       	}
      else
       	{
	 printf("%c is not a valid row\n\n", tok);
	 clear_buf();
	 continue;
       	}

      tok = get_token();
      if (isdigit(tok - '1')) //convert from alpha char to alpha num
       	{
	 m.wallcol = tok - 'a';
	 move_str[i++] = tok;
       	}
      else
       	{
	 printf("%c is not a valid column\n\n", tok);
	 clear_buf();
	 continue;
       	}


      tok = get_token();
      if (isdigit(tok))
       	{
	 m.wallrow = tok - '0';
	 move_str[i++] = tok;
       	}
      else
       	{
	 printf("%c is not a valid row\n\n", tok);
	 clear_buf();
	 continue;
       	}

      move_str[i] = '\0';

      //make sure it's a valid move
      if (!move_lookup(&m, movelist, move_count))
       	{
	 printf("%s is not a legal move\n", move_str);
	 continue;
       	}

      //User input verified
      done = TRUE;
     }
   while (done == FALSE);

   return m;
}

/*==============================================================================
 * get_token
 *
 * Retreives a token from stdin, ignores beginning whitespace.
 */
char get_token()
{
   char tok;
   tok = getc(movin);
   while (isspace(tok))
      tok = getc(movin);

   return tok;
}

/*==============================================================================
 * clear_buf
 *
 * Clears chars in the stdin buffer all the way up to and including the carriage 
 * return.
 */
void clear_buf()
{
   while (getc(movin) != '\n');
}


/*==============================================================================
 * move_lookup
 *
 * Compares a given move with a move with the moves in the given movelist.  If it's
 * found in the list, returns TRUE, otherwise returns FALSE.
 */
int move_lookup(move *m, move movelist[], int move_count)
{
   int i;

   for (i=0; i<move_count; i++)
     {
      if (m->queen != movelist[i].queen)
	 continue;
      if (m->tocol != movelist[i].tocol)
	 continue;
      if (m->torow != movelist[i].torow)
	 continue;
      if (m->wallcol != movelist[i].wallcol)
	 continue;
      if (m->wallrow != movelist[i].wallrow)
	 continue;
      else
       	{
	 printf("valid move\n");
	 return TRUE;
       	}
     }
   return FALSE;
}


// returns 1 if bit is set.
int test(state *s, uchar col, uchar row)
{
   //printf("sigh %d %d\n", col, row);
   if (row < 5)
     {
      if ( (s->blocks_bd[0] | s->white_bd[0] | s->black_bd[0] ) & 
	      (ull)1 << ((row*10) + col))
	 return 1;

      return 0;
     }
   else // row > 5
     {
      if ( (s->blocks_bd[1] | s->white_bd[1] | s->black_bd[1]) & 
	      (ull)1 << ((((row-5)*10) + col)))
       	{
	 return 1;
       	}
      return 0;
     }
}


// xor bit at col,row
int xor(ull bd[2], uchar col, uchar row)
{
   if (row < 5)
     {
      bd[0] ^= (ull)1 << ((row*10) + col);
     }
   else // row > 5
     {
      bd[1] ^= (ull)1 << ((((row-5)*10) + col));
     }
   return 1;
}

// takes a move that is to be made and returns a move that will
// undo it.
move savemove(state *s, move m)
{
   move temp;

   temp.wallcol = m.wallcol;
   temp.wallrow = m.wallrow;
   temp.queen = m.queen;

   if (s->turn == WHITE_PLAYER)
     {
      temp.tocol = s->white_q_x[m.queen];
      temp.torow = s->white_q_y[m.queen];
     }
   else
     {
      temp.tocol = s->black_q_x[m.queen];
      temp.torow = s->black_q_y[m.queen];
     }
   return temp;
}

int undomove(state *s, move m)
{
   s->turn ^= 3;

   if (s->turn == WHITE_PLAYER)
     {
      xor(s->white_bd, s->white_q_x[m.queen], s->white_q_y[m.queen]);
      s->white_q_x[m.queen] = m.tocol;
      s->white_q_y[m.queen] = m.torow;
      xor(s->white_bd, s->white_q_x[m.queen], s->white_q_y[m.queen]);
     }
   else
     {
      xor(s->black_bd, s->black_q_x[m.queen], s->black_q_y[m.queen]);
      s->black_q_x[m.queen] = m.tocol;
      s->black_q_y[m.queen] = m.torow;
      xor(s->black_bd, s->black_q_x[m.queen], s->black_q_y[m.queen]);
     }

   xor(s->blocks_bd, m.wallcol, m.wallrow);
   return 1;
}

// takes a move and does it. 
int makemove(state *s, move m)
{
   if (s->turn == WHITE_PLAYER)
     {
      xor(s->white_bd, s->white_q_x[m.queen], s->white_q_y[m.queen]);
      s->white_q_x[m.queen] = m.tocol;
      s->white_q_y[m.queen] = m.torow;
      xor(s->white_bd, s->white_q_x[m.queen], s->white_q_y[m.queen]);
     }
   else
     {
      xor(s->black_bd, s->black_q_x[m.queen], s->black_q_y[m.queen]);
      s->black_q_x[m.queen] = m.tocol;
      s->black_q_y[m.queen] = m.torow;
      xor(s->black_bd, s->black_q_x[m.queen], s->black_q_y[m.queen]);
     }

   xor(s->blocks_bd, m.wallcol, m.wallrow);
   s->turn ^= 3;
   return 1;
}

// print out a move struct
int pmove(move m)
{
   printf("%d) %d -> %c%d ---> %c%d, val = %d\n", onmove, 
	   m.queen, m.tocol+97, m.torow, m.wallcol+97, m.wallrow, m.val);

   if (movin != stdin) // ?
     {
      fprintf(movout, "%d  %c%d  %c%d\n", 
	      m.queen, m.tocol+97, m.torow, m.wallcol+97, m.wallrow);
      fflush(movout);
      fseek(movout,0,0);
      //sleep(6);
     }

   return 0;
}

// set up the state
int init(state *s)
{
   int i;

   s->blocks_bd[0] = s->blocks_bd[1] = 0;
   s->white_bd[0] = s->white_bd[1] = 0;
   s->black_bd[0] = s->black_bd[1] = 0;

   s->turn = WHITE_PLAYER;

   for (i=0; i < 4; i++)
     {
      s->white_q_x[i] = 0;
      s->white_q_y[i] = 0;
      s->black_q_x[i] = 0;
      s->black_q_y[i] = 0;
     }

   // some lines to trip things up

   //    xor(s->blocks_bd, 0,2);
   //    xor(s->blocks_bd, 1,2);
   //    xor(s->blocks_bd, 2,2);
   //    xor(s->blocks_bd, 3,2);
   //    xor(s->blocks_bd, 4,2);
   //    xor(s->blocks_bd, 5,2);
   //    xor(s->blocks_bd, 6,2);
   //    xor(s->blocks_bd, 7,2);
   //    xor(s->blocks_bd, 8,3);
   //    xor(s->blocks_bd, 9,2);

   // place queen on the board
   xor(s->white_bd, 6, 0);
   s->white_q_x[0] = 6;
   s->white_q_y[0] = 0;

   xor(s->white_bd, 3, 0);
   s->white_q_x[1] = 3;
   s->white_q_y[1] = 0;

   xor(s->white_bd, 0, 3);
   s->white_q_x[2] = 0;
   s->white_q_y[2] = 3;

   xor(s->white_bd,9,3);
   s->white_q_x[3] = 9;
   s->white_q_y[3] = 3;

   xor(s->black_bd, 3, 9);
   s->black_q_x[0] = 3;
   s->black_q_y[0] = 9;

   xor(s->black_bd, 6, 9);
   s->black_q_x[1] = 6;
   s->black_q_y[1] = 9;

   xor(s->black_bd, 0, 6);
   s->black_q_x[2] = 0;
   s->black_q_y[2] = 6;

   xor(s->black_bd,9,6);
   s->black_q_x[3] = 9;
   s->black_q_y[3] = 6;


   return 0;
}

int meta_init()
{
   if (!movin)
     {
#ifdef DEBUG
      printf("not using fifos\n");
#endif
      movin = stdin;
      movout = stdout;
     }

   pollstruct.fd = fileno(movin);
   pollstruct.events = POLLIN;
   pollstruct.revents = 0;

   return 1;
}

// test init function, used to set up potentially interesting 
// board states. Change call in main of init to x_init to put into
// action.
int x_init(state *s)
{
   int i;

   s->blocks_bd[0] = s->blocks_bd[1] = 0;
   s->white_bd[0] = s->white_bd[1] = 0;
   s->black_bd[0] = s->black_bd[1] = 0;

   s->turn = WHITE_PLAYER;

   for (i=0; i < 4; i++)
     {
      s->white_q_x[i] = 0;
      s->white_q_y[i] = 0;
      s->black_q_x[i] = 0;
      s->black_q_y[i] = 0;
     }

   // place queen on the board
   xor(s->white_bd, 0, 0);
   s->white_q_x[0] = 0;
   s->white_q_y[0] = 0;

   xor(s->white_bd, 1, 0);
   s->white_q_x[1] = 1;
   s->white_q_y[1] = 0;

   xor(s->white_bd, 0, 1);
   s->white_q_x[2] = 0;
   s->white_q_y[2] = 1;

   xor(s->white_bd, 6, 0);
   s->white_q_x[3] = 6;
   s->white_q_y[3] = 0;


   xor(s->black_bd, 8, 0);
   s->black_q_x[0] = 8;
   s->black_q_y[0] = 0;

   xor(s->black_bd, 2, 0);
   s->black_q_x[1] = 2;
   s->black_q_y[1] = 0;

   xor(s->black_bd, 2, 1);
   s->black_q_x[2] = 2;
   s->black_q_y[2] = 1;

   xor(s->black_bd, 2, 2);
   s->black_q_x[3] = 2;
   s->black_q_y[3] = 2;

   /*
      xor(s->blocks_bd, 1,1);
      xor(s->blocks_bd, 1,2);
      xor(s->blocks_bd, 0,2);
    */

   xor(s->blocks_bd, 3,0);
   xor(s->blocks_bd, 3,1);
   xor(s->blocks_bd, 3,2);
   xor(s->blocks_bd, 3,3);
   xor(s->blocks_bd, 0,3);
   xor(s->blocks_bd, 1,3);
   xor(s->blocks_bd, 2,3);

   xor(s->blocks_bd, 4,3);
   xor(s->blocks_bd, 4,4);
   xor(s->blocks_bd, 5,4);
   xor(s->blocks_bd, 6,4);
   xor(s->blocks_bd, 7,4);
   xor(s->blocks_bd, 8,4);
   xor(s->blocks_bd, 9,4);

   /*
      xor(s->blocks_bd, 4,2);
      xor(s->blocks_bd, 5,2);
      xor(s->blocks_bd, 6,2);
      xor(s->blocks_bd, 7,2);
      xor(s->blocks_bd, 8,2);
      xor(s->blocks_bd, 9,2);
    */

   /*
      xor(s->blocks_bd, 4,0);
      xor(s->blocks_bd, 4,1);
      xor(s->blocks_bd, 5,0);
      xor(s->blocks_bd, 5,1);
    */



   /*
      xor(s->blocks_bd, 5,0);
      xor(s->blocks_bd, 5,1);
      xor(s->blocks_bd, 6,1);
      xor(s->blocks_bd, 7,0);
      xor(s->blocks_bd, 7,1);
      xor(s->blocks_bd, 8,1);
      xor(s->blocks_bd, 9,1);
      xor(s->blocks_bd, 9,0);
    */


   return 0;
}

#ifndef GAMAZONS
/*==============================================================================
 * main 
 *
 *
 */
int main(int argc, char *argv[])
{
   state *s;
   //struct move m;
   move temp;
   int i;

   // Initialize game states
   for (i=0; i<100; i++)
      states.s[i] = (state *) malloc(sizeof(state));
   states.current_state = 0;
   states.max_state = 0;
   s = states.s[0];

   parse_args(argc, argv);
   meta_init();
   init(s);

   printf("size of move = %d\n", sizeof(move));
   printf("size of state = %d\n", sizeof(state));

   pboard(*s);

   //test_fdiag(s);
   //test_bdiag(s);
   //test_gen_web_stream(s);
   //test_put_col(s);
   //test_put_row(s);
   //test_put_fdiag(s);
   //test_put_bdiag(s);

#ifdef DEBUG_HEVAL
   xor(s->white_bd, 9, 3);
   xor(s->white_bd, 8, 2);
   s->white_q_x[3] = 8;
   s->white_q_y[3] = 2;
   xor(s->blocks_bd, 8, 3);
   s->turn = BLACK_PLAYER;

   pboard(*s);
   printf("board value is %d\n", HEVAL(s));

   pbvec(s->white_bd[0], s->white_bd[1]);
#endif

#ifndef DEBUG_HEVAL

   /* the main play loop. Gets a move, does a move, repeats.
      lobal ok is set to 1 for use with timeouts 
    */
   for (;;)
     {
      dup_state(s, states.s[++(states.current_state)]);
      s = states.s[states.current_state];
      if (states.current_state > states.max_state)
	 states.max_state = states.current_state;

      if (options.white_player == HUMAN)
       	{
	 temp = getmove(s, 1);
	 makemove(s, temp);
	 onmove++;
	 pboard(*s);
       	}
      else
       	{
	 ok = 1;
	 start = time(NULL);
	 temp = isearch(s, NOTHINK);
	 printf("WHITE selected: ");
	 pmove(temp);
	 makemove(s,temp);
	 onmove++;
	 pboard(*s);
       	}

      dup_state(s, states.s[++(states.current_state)]);
      s = states.s[states.current_state];
      if (states.current_state > states.max_state)
	 states.max_state = states.current_state;

      if (options.black_player == HUMAN)
       	{
	 temp = getmove(s, 2);
	 makemove(s, temp);
	 onmove++;
	 pboard(*s);
       	}
      else
       	{
	 ok = 1;
	 start = time(NULL);
	 temp = isearch(s, NOTHINK);
	 printf("BLACK selected: ");
	 pmove(temp);
	 makemove(s,temp);
	 onmove++;
	 pboard(*s);
       	}
     }
#endif

   return 0;

}
#endif //ifndef GAMAZONS


#ifdef GAMAZONS
/*==============================================================================
 * init_engine
 *
 * 
 * 
 */
void init_engine()
{
   state *s;
   //struct move m;
   move temp;
   int i;

   srand(time(NULL));

   // Initialize game states
   for (i=0; i<100; i++)
      states.s[i] = (state *) malloc(sizeof(state));
   states.current_state = 0;
   states.max_state = 0;

   s = states.s[0];
   s->turn = WHITE_PLAYER;
   s->winner = 0;
   state_hash = create_hash(s);


   meta_init();
   init(s);
   dup_state(s, states.s[++(states.current_state)]);

   /* set default options */
   options.engine.maxdepth=20;
   options.engine.maxwidth=3000;
   options.engine.timeout=1;
   options.white_player=HUMAN;
   options.black_player=HUMAN;
   options.print_statistics=FALSE;


   load_images_from_theme(PACKAGE_DATA_DIR "/gamazons/default.theme");
   /*
   strcpy(options.images.white_piece, PACKAGE_DATA_DIR "/pixmaps/gamazons/white.png");
   strcpy(options.images.black_piece, PACKAGE_DATA_DIR "/pixmaps/gamazons/black.png");
   strcpy(options.images.white_sq, PACKAGE_DATA_DIR "/pixmaps/gamazons/white_square.png");
   strcpy(options.images.grey_sq, PACKAGE_DATA_DIR "/pixmaps/gamazons/grey_square.png");
   strcpy(options.images.arrow_sq, PACKAGE_DATA_DIR "/pixmaps/gamazons/black_square.png");
   */

#ifdef DEBUG
   printf("white piece image = %s\n", options.images.white_piece);
#endif
   load_values_from_file();

}


/*==============================================================================
 * load_values_from_file
 *
 * If a .gamazons file is found in the user's home directory, it will attempt to
 * load the values stored therein.  Any variables it doesn't recognize will be
 * silently ignored.
 */
void load_values_from_file()
{
   char *home, file[256];
   FILE *rc_fd;
   char variable[256];
   char buffer[256];
   int value;
   char ch;


   if (!(home = getenv("HOME")))
      return;

   strcpy(file, home);
   strcat(file, "/.gamazons");
#ifdef DEBUG
   printf("looking for the file %s\n", file);
#endif

   rc_fd = fopen(file, "r");
   if(rc_fd == NULL)
      return;

   while (fscanf(rc_fd, "%s", variable) != EOF)
     {
      while (ch = fgetc(rc_fd))
	{
	 if (ch == EOF)
	    return;
	 if (ch == '=')
	    break;
	}

      if (strcmp(variable, "WHITE_PLAYER") == 0)
	{
	 fscanf(rc_fd, "%d", &value);
	 options.white_player = value;
	}
      else if (strcmp(variable, "BLACK_PLAYER") == 0)
	{
	 fscanf(rc_fd, "%d", &value);
	 options.black_player = value;
	}
      else if (strcmp(variable, "TIMEOUT") == 0)
	{
	 fscanf(rc_fd, "%d", &value);
	 options.engine.timeout = value;
	}
      else if (strcmp(variable, "MAXWIDTH") == 0)
	{
	 fscanf(rc_fd, "%d", &value);
	 options.engine.maxwidth = value;
	}
      else if (strcmp(variable, "MAXDEPTH") == 0)
	{
	 fscanf(rc_fd, "%d", &value);
	 options.engine.maxdepth = value;
	}
      else if (strcmp(variable, "WHITE_PIECE") == 0)
	{
	 fscanf(rc_fd, "%s", buffer);
	 strcpy(options.images.white_piece, buffer);
	}
      else if (strcmp(variable, "BLACK_PIECE") == 0)
	{
	 fscanf(rc_fd, "%s", buffer);
	 strcpy(options.images.black_piece, buffer);
	}
      else if (strcmp(variable, "WHITE_SQUARE") == 0)
	{
	 fscanf(rc_fd, "%s", buffer);
	 strcpy(options.images.white_sq, buffer);
	}
      else if (strcmp(variable, "GREY_SQUARE") == 0)
	{
	 fscanf(rc_fd, "%s", buffer);
	 strcpy(options.images.grey_sq, buffer);
	}
      else if (strcmp(variable, "ARROW_SQUARE") == 0)
	{
	 fscanf(rc_fd, "%s", buffer);
	 strcpy(options.images.arrow_sq, buffer);
	}
      else if (strcmp(variable, "DRAW_GRID") == 0)
	{
	 fscanf(rc_fd, "%s", buffer);
	 if (strcmp(buffer, "TRUE") == 0)
	    options.images.grid = TRUE;
	 else
	    options.images.grid = FALSE;
	}


     }

   fclose(rc_fd);

}

/*==============================================================================
 * store_values_in_file
 *
 * Creates/overwrites a .gamazons file in the user's home directory.  Stores
 * the values in the options struct in it.
 */
void store_values_in_file()
{
   char *home, file[256];
   FILE *rc_fd;

   if (!(home = getenv("HOME")))
      return;

   strcpy(file, home);
   strcat(file, "/.gamazons");
#ifdef DEBUG
   printf("looking for the file %s\n", file);
#endif

   rc_fd = fopen(file, "w");
   if (rc_fd == NULL)
      return;
   
   fprintf(rc_fd, "WHITE_PLAYER = ");
   fprintf(rc_fd, "%d\n", options.white_player);

   fprintf(rc_fd, "BLACK_PLAYER = ");
   fprintf(rc_fd, "%d\n", options.black_player);

   fprintf(rc_fd, "TIMEOUT = ");
   fprintf(rc_fd, "%d\n", options.engine.timeout);

   fprintf(rc_fd, "MAXWIDTH = ");
   fprintf(rc_fd, "%d\n", options.engine.maxwidth);

   fprintf(rc_fd, "MAXDEPTH = ");
   fprintf(rc_fd, "%d\n", options.engine.maxdepth);

   fprintf(rc_fd, "WHITE_PIECE = ");
   fprintf(rc_fd, "%s\n", options.images.white_piece);

   fprintf(rc_fd, "BLACK_PIECE = ");
   fprintf(rc_fd, "%s\n", options.images.black_piece);

   fprintf(rc_fd, "WHITE_SQUARE = ");
   fprintf(rc_fd, "%s\n", options.images.white_sq);

   fprintf(rc_fd, "GREY_SQUARE = ");
   fprintf(rc_fd, "%s\n", options.images.grey_sq);

   fprintf(rc_fd, "ARROW_SQUARE = ");
   fprintf(rc_fd, "%s\n", options.images.arrow_sq);

   fprintf(rc_fd, "DRAW_GRID = ");
   if (options.images.grid == TRUE)
      fprintf(rc_fd, "%s\n", "TRUE");
   else
      fprintf(rc_fd, "%s\n", "FALSE");

   fclose(rc_fd);
}

/*==============================================================================
 * load_images_from_theme
 *
 * This file will read image paths from a theme file.  These values get loaded 
 * into the options struct, and subsequently used to draw the board.
 */
void load_images_from_theme(char *theme)
{
   char *home, file[256];
   FILE *theme_fd;
   char variable[256];
   char buffer[256];
   int value;
   char ch;


   theme_fd = fopen(theme, "r");
   if(theme_fd == NULL)
     {
      printf("Can't open theme file %s\n", theme);
      exit(1);
     }

   while (fscanf(theme_fd, "%s", variable) != EOF)
     {
      while (ch = fgetc(theme_fd))
	{
	 if (ch == EOF)
	    return;
	 if (ch == '=')
	    break;
	}

      if (strcmp(variable, "WHITE_PIECE") == 0)
	{
	 fscanf(theme_fd, "%s", buffer);
	 strcpy(options.images.white_piece, PACKAGE_DATA_DIR "/pixmaps/gamazons/");
	 strcat(options.images.white_piece, buffer);
	}
      else if (strcmp(variable, "BLACK_PIECE") == 0)
	{
	 fscanf(theme_fd, "%s", buffer);
	 strcpy(options.images.black_piece, PACKAGE_DATA_DIR "/pixmaps/gamazons/");
	 strcat(options.images.black_piece, buffer);
	}
      else if (strcmp(variable, "WHITE_SQUARE") == 0)
	{
	 fscanf(theme_fd, "%s", buffer);
	 strcpy(options.images.white_sq, PACKAGE_DATA_DIR "/pixmaps/gamazons/");
	 strcat(options.images.white_sq, buffer);
	}
      else if (strcmp(variable, "GREY_SQUARE") == 0)
	{
	 fscanf(theme_fd, "%s", buffer);
	 strcpy(options.images.grey_sq, PACKAGE_DATA_DIR "/pixmaps/gamazons/");
	 strcat(options.images.grey_sq, buffer);
	}
      else if (strcmp(variable, "ARROW_SQUARE") == 0)
	{
	 fscanf(theme_fd, "%s", buffer);
	 strcpy(options.images.arrow_sq, PACKAGE_DATA_DIR "/pixmaps/gamazons/");
	 strcat(options.images.arrow_sq, buffer);
	}
      else if (strcmp(variable, "DRAW_GRID") == 0)
	{
	 fscanf(theme_fd, "%s", buffer);
	 if (strcmp(buffer, "TRUE") == 0)
	    options.images.grid = TRUE;
	 else
	    options.images.grid = FALSE;
	}


     }

   fclose(theme_fd);


}
#endif

/*============================================================================== 
 * print_usage_menu 
 *
 * Displays a list of all command line options
 */
void print_usage_menu()
{
   printf("Amazons Usage:\n");
   printf("amazons [OPTIONS]\n");
   printf("     -d #:   Sets the maximum search depth\n");
   printf("     -h:     Prints this help menu\n");
   printf("     -p #:   User plays against the computer (1 white, 2 black)\n");
   printf("     -s:     Prints out interesting statistics\n");
   printf("     -t #:   Sets the time limit between moves\n");
   printf("\n\n");
}


/* parse args
 *
 * Handles the arguments passed into the program.  
 *
 * Note: this expects all arguments to be listed separately, 
 * each with it's own '-'
 */
void parse_args(int argc, char *argv[])
{
   int i = 1;

   //Set defaults
   options.engine.maxdepth=20;
   options.engine.maxwidth=5000;
   options.engine.timeout=2;
   options.white_player=HUMAN;
   options.black_player=AI;
   options.print_statistics=FALSE;


   while (i < argc)
     {
      switch(argv[i][1])
       	{
	  case 'd':
	      options.engine.maxdepth = atoi(argv[++i]);
	      i++;
	      break;
	  case 'h':
	      print_usage_menu();
	      exit(0);
	  case 'p':
	      if (atoi(argv[++i]) == 1)
		 options.white_player = HUMAN;
	      else
		 options.black_player = HUMAN;
	      i++;
	      break;
	  case 'f':
#ifdef DEBUG
	      printf("opening movin\n");
#endif
	      movin = fopen(argv[++i], "r+");
#ifdef DEBUG
	      printf("success\n");
	      printf("opening movout\n");
#endif
	      movout = fopen(argv[++i], "r+");
#ifdef DEBUG
	      printf("success\n");
#endif
	      //fprintf(fifop, "wubba wubba\n");
	      //fflush(fifop);
	      //printf("open success\n");
	      i++;
	      break;
	  case 's':
	      options.print_statistics = TRUE;
	      i++;
	      break;
	  case 't':
	      options.engine.timeout = atoi(argv[++i]);
	      i++;
	      break;
	  case 'w':
	      options.engine.maxdepth = atoi(argv[++i]);
	      i++;
	      break;
	  default:
	      printf("Unknown argument  %s\n", argv[i]);
	      print_usage_menu();
	      exit(1);
       	}
     }
}


void print_stats()
{

   printf("TT Stats:\n");
   printf("   # nodes over written: %d\n", tt_overwrite);
   printf("   # of nodes stored:    %d\n", tt_stores);
   printf("   # of updates made:    %d\n", tt_updates);
   printf("   # of lookups made:    %d\n", tt_lookups);
   printf("   # of lookups found:   %d\n", tt_lookup_finds);
   printf("\n");
   printf("Heuristic Stats:\n");
   printf("   # of heuristic calls  %d\n", heval_calls);
}

void dup_state(state *s_old, state *s_new)
{
   int i;

   s_new->white_bd[0] = s_old->white_bd[0];
   s_new->white_bd[1] = s_old->white_bd[1];

   s_new->blocks_bd[0] = s_old->blocks_bd[0];
   s_new->blocks_bd[1] = s_old->blocks_bd[1];

   s_new->black_bd[0] = s_old->black_bd[0];
   s_new->black_bd[1] = s_old->black_bd[1];

   for (i=0; i<4; i++)
     {
      s_new->white_q_x[i] = s_old->white_q_x[i]; 
      s_new->black_q_x[i] = s_old->black_q_x[i];

      s_new->white_q_y[i] = s_old->white_q_y[i]; 
      s_new->black_q_y[i] = s_old->black_q_y[i]; 
     }

   s_new->turn = s_old->turn;
#ifdef DEBUG
   printf("old turn is %d, new turn is %d\n", s_old->turn, s_new->turn);
#endif
   s_new->value = s_old->value;
   s_new->depth = s_old->depth;
   s_new->winner = s_old->winner;
}


