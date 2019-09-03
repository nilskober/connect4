// Copyright 2019 Nils Kober
// Author: Nils Kober <nils.kober@students.uni-freiburg.de>
// Published under MIT License

#ifndef SRC_IO_FOUR_IO_H_
#define SRC_IO_FOUR_IO_H_

#include <stdio.h>
#include <stdbool.h>
#include "./../game/four_game.h"

#define EMPTY_SYMBOL ' '
#define PLAYER_A_SYMBOL '*'
#define PLAYER_B_SYMBOL 'o'

#define FORMAT_NONE 0  // to_move will not be printed
#define FORMAT_READABLE 1
#define FORMAT_MACHINE 2
#define FORMAT_READABLE_NONE 3  // Readable but without to_move

/* Output the given matrix to the given file stream using the constants above
and declared in const.h.
Any number not matching any of the constants in const.h will the printed as
EMPTY_SYMBOL.
Depending on mode the player to move will be outputed either not at all,
in a human readable format or in a machine readable format. */
void output_to_stream(FILE *f, game_state *game, unsigned char mode);

/* Call output_to_stream() with a file stream matching to the given name.
Return false on failure, otherwise true. */
bool output_to_file(const char f_name[], game_state *game, unsigned char mode);

/* Call output_to_stream() with f = stdout and mode = FORMAT_READABLE. */
void output(game_state *game);

/* Call output_to_file with mode = FORMAT_MACHINE. */
bool save(const char f_name[], game_state *game);

/* Read input from the given file path and store it in the given instance of
game_state using FORMAT_MACHINE.
Return true on success, otherwise false. */
bool read_file(const char f_name[], game_state *g);

/* Wait for input of integer number between 1 and COLUMNS, followed by enter.
Return that input. In case of an illegal input, return 0. */
unsigned char read_number();

#endif  // SRC_IO_FOUR_IO_H_
