## Process this file with automake to produce Makefile.in

INCLUDES = \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(datadir)/locale"\" \
	@PACKAGE_CFLAGS@

bin_PROGRAMS = gamazons 

gamazons_SOURCES = \
	main.c \
	support.c support.h \
	interface.c interface.h \
	callbacks.c callbacks.h \
	board.c board.h \
	position.h \
	eval.c \
	moves.c \
	unit-test.c unit-test.h \
	amazons.h 

gamazons_INCLUDES = -DGAMAZONS=1

gamazons_CFLAGS = -O2 -DGAMAZONS=1

gamazons_HELP = gamazons.html topic.dat
gamazons_BITMAPS = white.png black.png

EXTRA_DIST = $(gamazons_BITMAPS) $(gamazons_HELP)
gamazonsbitmapsdir = $(datadir)/pixmaps
gamazonsbitmaps_DATA = $(gamazons_BITMAPS)

gamazonshelpdir = $(datadir)/gnome/help/gamazons/C
gamazonshelp_DATA = $(gamazons_HELP)

gamazons_LDADD = @PACKAGE_LIBS@

##amazons_SOURCES = \
##	eval.c \
##	moves.c \
##	unit-test.c unit-test.h \
##	amazons.h 
##
##amazons_CFLAGS = -O2
##
##amazons_LDADD = a_moves.o
