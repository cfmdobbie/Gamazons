## Process this file with automake to produce Makefile.in

INCLUDES = \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(datadir)/locale"\" \
	@PACKAGE_CFLAGS@

bin_PROGRAMS = gamazons amazons

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

amazons_SOURCES = \
	eval.c \
	moves.c \
	unit-test.c unit-test.h \
	amazons.h 

amazons_INCLUDES = -DAMAZONS=1

gamazons_LDADD = @PACKAGE_LIBS@

