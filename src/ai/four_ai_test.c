// Copyright 2019 Nils Kober
// Author: Nils Kober <nils.kober@students.uni-freiburg.de>
// Published under MIT License

#include <assert.h>
#include "four_ai.h"
#include "./../game/four_game.h"
#include "./../debug/four_debug.h"

void winning_gameOverA_PlayerA();
void winning_depth0NoWinner_0();
void winning_depth1NoWinner_0();
void winning_depth1AWins_PlayerA();
void winning_depth3AWins_PlayerA();
void winning_depth3NoWinner_0();

int main(void) {
    winning_gameOverA_PlayerA();
    debug_print(DEBUG_AI_1, "%s\n\n", "");
    winning_depth0NoWinner_0();
    debug_print(DEBUG_AI_1, "%s\n\n", "");
    winning_depth1NoWinner_0();
    debug_print(DEBUG_AI_1, "%s\n\n", "");
    winning_depth1AWins_PlayerA();
    debug_print(DEBUG_AI_1, "%s\n\n", "");
    winning_depth3AWins_PlayerA();
    debug_print(DEBUG_AI_1, "%s\n\n", "");
    winning_depth3NoWinner_0();
    debug_print(DEBUG_AI_1, "%s\n\n", "");
    return 0;
}


void winning_gameOverA_PlayerA() {
    game_state g;
    game_state_init(&g);
    exec_move(&g, 1);
    exec_move(&g, 2);
    exec_move(&g, 1);
    exec_move(&g, 2);
    exec_move(&g, 1);
    exec_move(&g, 2);
    exec_move(&g, 1);
    // arbitrary depth
    assert(winning(&g, 5) == PLAYER_A_NUM);
}

void winning_depth0NoWinner_0() {
    game_state g;
    game_state_init(&g);
    exec_move(&g, 1);
    exec_move(&g, 2);
    assert(winning(&g, 0) == 0);
}

void winning_depth1NoWinner_0() {
    game_state g;
    game_state_init(&g);
    exec_move(&g, 1);
    exec_move(&g, 2);
    assert(winning(&g, 1) == 0);
}

void winning_depth1AWins_PlayerA() {
    game_state g;
    game_state_init(&g);
    exec_move(&g, 1);
    exec_move(&g, 2);
    exec_move(&g, 1);
    exec_move(&g, 2);
    exec_move(&g, 1);
    exec_move(&g, 2);

    // arbitrary depth
    assert(winning(&g, 1) == PLAYER_A_NUM);
}

void winning_depth3AWins_PlayerA() {
    game_state g;
    game_state_init(&g);
    exec_move(&g, 3);
    exec_move(&g, 3);
    exec_move(&g, 3);
    exec_move(&g, 2);
    exec_move(&g, 2);
    exec_move(&g, 4);
    exec_move(&g, 4);
    exec_move(&g, 1);
    exec_move(&g, 1);
    exec_move(&g, 5);
    exec_move(&g, 5);
    exec_move(&g, 5);
    exec_move(&g, 4);
    exec_move(&g, 1);
    exec_move(&g, 2);
    exec_move(&g, 5);

    /* current state:
    (only relevant counters from player A)

      * *
     *   *
    
    */

    assert(winning(&g, 3) == PLAYER_A_NUM);
}

void winning_depth3NoWinner_0() {
    game_state g;
    game_state_init(&g);
    exec_move(&g, 0);
    exec_move(&g, 1);
    exec_move(&g, 0);
    exec_move(&g, 1);

    assert(winning(&g, 3) == 0);
}
