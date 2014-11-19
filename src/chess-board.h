/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 8; tab-width: 8 -*- */
/* board.h
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

#ifndef BOARD_H_
#define BOARD_H_

#include <gnome.h>
#include "makros.h"
#include "position.h"

#ifdef __cplusplus
extern "C" {
#pragma }
#endif /* __cplusplus */

#define TYPE_BOARD			(board_get_type ())
#define BOARD(obj)			(GTK_CHECK_CAST ((obj), TYPE_BOARD, Board))
#define BOARD_CLASS(klass)		(GTK_CHECK_CLASS_CAST ((klass), TYPE_BOARD, BoardClass))
#define IS_BOARD(obj)			(GTK_CHECK_TYPE ((obj), TYPE_BOARD))
#define IS_BOARD_CLASS(klass)		(GTK_CHECK_CLASS_TYPE ((obj), TYPE_BOARD))


typedef struct _Board        Board;
typedef struct _BoardPrivate BoardPrivate;
typedef struct _BoardClass   BoardClass;

struct _Board {
	GnomeCanvas parent;

	BoardPrivate *priv;
};

struct _BoardClass {
	GnomeCanvasClass parent_class;

	void (* move) (Board *board, Square from, Square to);
	void (* flip) (Board *board, gboolean flip);
};



GtkType    board_get_type        (void);
GtkWidget *board_new             (void);

Position * board_get_position    (Board    *board);
void       board_set_position    (Board    *board,
				  Position *pos);

guint32    board_get_light_color (Board    *board);
void       board_set_light_color (Board    *board,
				  guint32   rgba);
guint32    board_get_dark_color  (Board    *board);
void       board_set_dark_color  (Board    *board,
				  guint32   rgba);
void       board_set_flip        (Board    *board,
				  gboolean  f);
void       board_flip            (Board    *board);

void       board_move            (Board    *board,
				  Square    from,
				  Square    to);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* BOARD_H_ */
