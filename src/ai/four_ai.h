// Copyright 2019 Nils Kober
// Author: Nils Kober <nils.kober@students.uni-freiburg.de>
// Published under MIT License

#ifndef SRC_AI_FOUR_AI_H_
#define SRC_AI_FOUR_AI_H_

#include "./../game/four_game.h"

#define AI_DEFAULT_DIFF 6

/* Calculate a / the best move for the player whose turn it is,
using the given search depth.
Return the respective column. */
unsigned char ai_calc_move(game_state *g, unsigned char depth);

/* Calculate which player is able to win the game on its own in the given
situation.
Return the respective number or 0 if no player is able to do so. */
unsigned char winning(game_state *g, unsigned char depth);

#endif  // SRC_AI_FOUR_AI_H_
