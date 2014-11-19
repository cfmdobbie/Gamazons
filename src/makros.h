/* 
 * Copyright (C) 1999 Robert Wilhelm
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */

#ifndef _MAKROS_H_
#define _MAKROS_H_

#include <glib.h>


/* Types */
/*
typedef gushort Square;
typedef gchar   Piece;
*/

/* Various empty defines */
#define NONE		0

/* Generated movelist */
#define AB_ZUGL		512	/*  Length of list generated moves	*/
#define AB_ZUG_S	256	/*  Beginning of generated capture moves*/


/* Notation types */
#define	SAN		0	/*  Standard algebraic notation		*/
#define	COORD		1	/*  Coordinate notation			*/

/* Game results */
#define	GAME_NONE	0	/*  No game			        */
#define	GAME_PAUSED	1	/*  Game is paused			*/
#define	GAME_PROGRESS	2	/*  Game is in progress			*/
#define	GAME_ABORTED	3	/*  Game was aborted			*/
#define	GAME_WHITE	4	/*  White won the game			*/
#define	GAME_BLACK	5	/*  Black won the game			*/
#define	GAME_DRAW	6	/*  Draw			        */

/* Board window modes */
#define	COMPUTER_BLACK	1
#define	COMPUTER_WHITE	2
#define	AUTOPLAY	3
#define	ANALYSE		4
#define	HUMANS		5

#define PIECE_SIZE 40

#define  OL            9     /********************************************/
#define  OM           10     /*                                          */
#define  OR           11     /*            OL |  OM  | OR                */
#define  LI           -1     /*           ----+------+----               */
#define  RE            1     /*            LI | FELD | RE                */
#define  UL          -11     /*           ----+------+----               */
#define  UM          -10     /*            UL |  UM  | UR                */
#define  UR           -9     /********************************************/

/*************************************************************************/
/*                         Figuren      Pieces                           */
/*************************************************************************/
/*                                                                       */
/*      weiss   white  32 + x      x = 1  Bauer     Pawn                 */
/*      schwarz black  64 + x          2  Springer  Knight               */
/*      leer    empty  0               3  Laeufer   Bishop               */
/*      rand    border 16              4  Turm      Rook                 */
/*                                     5  Dame      Queen                */
/*                                     6  Koenig    King                 */
/*                                                                       */
/*************************************************************************/

#define WP		33	 /*  white pawn   */
#define WN		34	 /*  white knight */
#define WB		35	 /*  white bishop */
#define WR		36	 /*  white rook   */
#define WQ		37	 /*  white queen  */
#define WK		38	 /*  white king   */
#define BP		65	 /*  black pawn   */
#define BN		66	 /*  black knight */
#define BB		67	 /*  black bishop */
#define BR		68	 /*  black rook   */
#define BQ		69	 /*  black queen  */
#define BK		70	 /*  black king	  */
#define EMPTY     0              /*  empty	  */
#define BORDER    16             /*  border (illegal) */

#define WPIECE(c) ((c) & 32)   /* white piece? */
#define BPIECE(c) ((c) & 64)   /* black piece? */

/****************************************************************/
/*                      Squares                                 */
/****************************************************************/

#define A1  1
#define B1  2
#define C1  3
#define D1  4
#define E1  5
#define F1  6
#define G1  7
#define H1  8
#define I1  9
#define J1 10

#define A2 11
#define B2 12
#define C2 13
#define D2 14
#define E2 15
#define F2 16
#define G2 17
#define H2 18
#define I2 19
#define J2 20

#define A3 21
#define B3 22
#define C3 23
#define D3 24
#define E3 25
#define F3 26
#define G3 27
#define H3 28
#define I3 29
#define J3 30

#define A4 31
#define B4 32
#define C4 33
#define D4 34
#define E4 35
#define F4 36
#define G4 37
#define H4 38
#define I4 39
#define J4 40

#define A5 41
#define B5 42
#define C5 43
#define D5 44
#define E5 45
#define F5 46
#define G5 47
#define H5 48
#define I5 49
#define J5 50

#define A6 51
#define B6 52
#define C6 53
#define D6 54
#define E6 55
#define F6 56
#define G6 57
#define H6 58
#define I6 59
#define J6 60

#define A7 61
#define B7 62
#define C7 63
#define D7 64
#define E7 65
#define F7 66
#define G7 67
#define H7 68
#define I7 69
#define J7 70 

#define A8 71 
#define B8 72 
#define C8 73 
#define D8 74 
#define E8 75 
#define F8 76 
#define G8 77 
#define H8 78 
#define I8 79 
#define J8 80 

#define A9 81 
#define B9 82 
#define C9 83 
#define D9 84 
#define E9 85 
#define F9 86 
#define G9 87 
#define H9 88 
#define I9 89 
#define J9 90 

#define A10 91
#define B10 92
#define C10 93
#define D10 94
#define E10 95
#define F10 96
#define G10 97
#define H10 98
#define I10 99
#define J10 100

#endif /* _MAKROS_H_ */

