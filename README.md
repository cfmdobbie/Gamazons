# Gamazons

> GNOME Amazons, taken from http://www.yorgalily.org/gamazons/

> This software was written by *yorgasor*, dates from August to November 2002 and was released under the GPL at the above link.  Uploaded to GitHub for preservation reasons, and also to provide an easily-browseable version of the source code.

> Below is a rough conversion of the source webpage to Markdown.


## [Download](http://www.yorgalily.org/gamazons/download.html)

## The Game

Amazons is a game played on a 10x10 chess board. Each side has four pieces (amazons) that move like chess queens (in a straight line in any direction). Instead of capturing pieces like in chess, the game is determined based on who moves last.

Each move consists of two parts. First an amazon moves to a new square and then fires an arrow to another square (the arrow is fired in a straight line in any direction from the square the amazon landed on). The square the arrow lands on becomes a permenant block for the rest of the game. No one can move over it, or fire an arrow over it. Every turn an amazon must move and fire an arrow, so every turn there is one less square available on the board. Try and block in your opponent or section off a good chunk of the board for yourself.

## Basic Instructions:

This is a Gnome 2 app, so that must be installed on your system for it to work. Other than that, from the main directory, type "./configure" to generate the necessary makefiles. Then make, make install to compile and install the game. Then type gamazons to start the game.

**Note:** I've heard reports of the ./configure erroring out on RH8 with the following message:

    checking for libgnomeui-2.0... Package libgnomeui-2.0 was not found in the pkg-config search path.
    Perhaps you should add the directory containing `libgnomeui-2.0.pc' to the PKG_CONFIG_PATH environment variable
    No package 'libgnomeui-2.0' found

This problem can be fixed by installing the libgnomeui-devel-2.0.3-3 RPM file.

You can set the player settings from the settings->player menu. You can set it to play AI vs AI or whatever you like.

However, I do have a few default option overrides. For instance, when you get near the end of the game and you don't feel like brainlessly moving a bunch of pieces that are already blocked off into their own areas, you can click on "Auto Finish" which will set both players as AI with a 1 second think time. Also, if you get a little tired of waiting for the AI to move (perhaps you set the time to think too long), you can click on the Force Move button and make him move right then.

Things that aren't implemented yet are the network and help menus. Also the undo button doesn't do anything yet (although I've pretty much got the framework to do it).

## Future Project Goals

### Primary Goals (Done):

- Drag queens around the board to move
- Click on square to fire (maybe have pointer change to a target)
- Specify various game settings: 
  - Who plays what: CPU vs CPU, hum vs CPU, hum vs hum, 
  - Search time 
  - Search width 

### Secondary Goals:

- Allow network play
- When moving a piece, highlight the square you're over so the user knows for sure where the piece will land. Maybe have a red highlight for illegal moves, and blue for legal ones. Do the same while looking for a square to fire an arrow at.
- Include a countdown clock for both players
- Setup mode, allows person to set the board up before playing

### Ternary Goals:

- Some kind of high score table
- Save your game history to a file

### Amazon Improvements:

- Include heuristics based on the difficulty level specified by the user
- Randomly pick one of the top 5 moves (or a top move within a certain range).
- Get MTD(f) working
- Implement current state game analysis 
  - Decides what kind of heuristics to use in the search 
  - Uses a graph representation of the board, using path following algs to determine various conditions (are queens isolated? how many squares are really usable? etc...)
- Find new, more intelligent heuristics.

## Licensing

This program is licensed under the GPL.

## Comments/Bugs/Patches

Like the game? Think it sucks? Got code to make it better? Just drop me a note at yorgasor AT yorgalily DOT org.

## Other Resources

If you're interested in more in Amazon game theory and the AI behind the game, you can find all the information you can imagine from [Tegos'](http://www.cs.ualberta.ca/~tegos/amazons/) Amazons page, as well as [Buro's](http://www.cs.ualberta.ca/~mburo/) page.

