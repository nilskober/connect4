// Copyright 2019 Nils Kober
// Author: Nils Kober <nils.kober@students.uni-freiburg.de>
// Published under MIT License

#include <stdlib.h>
#include <stdbool.h>
#include "four_ai.h"
#include "./../game/four_game.h"
#include "./../debug/four_debug.h"
#include "./../io/four_io.h"

// ____________________________________
unsigned char ai_calc_move(game_state *g, unsigned char depth) {
    unsigned char res = 0;
    unsigned char loosing[MAX_DEPTH][COLUMNS];
    bool def_loosing[MAX_DEPTH];
    for (int i = 0; i < MAX_DEPTH; i++) def_loosing[i] = true;

    // Check the for the shortest winning / loosing possibilities at first.
    for (unsigned char cur_dep = 0; cur_dep < depth; cur_dep++) {
        for (unsigned char j = 0; j < COLUMNS; j++) {
            debug_print(DEBUG_AI_1,
            "four_ai.c [ai_calc_move]: column: %d\n", j);
            if (exec_move(g, j)) {
                res = winning(g, cur_dep);
                revert_move(g, j);
                if (res == g->to_move) {
                    return j;
                } else if (res == 0) {
                    def_loosing[cur_dep] = false;
                    loosing[cur_dep][j] = 0;
                } else {
                    loosing[cur_dep][j] = 1;
                }
            }
        }
    }
    unsigned char prio[COLUMNS];
    for (unsigned char i = 0; i < COLUMNS; i++) {
        prio[i] = i;
    }
    for (unsigned char i = 0; i < COLUMNS; i++) {
        unsigned char r = (unsigned char) (rand() % COLUMNS);
        unsigned char temp = prio[i];
        prio[i] = prio[r];
        prio[r] = temp;
    }
    for (unsigned char i = 0; i < COLUMNS; i++) {
        debug_print(DEBUG_AI_1,
            "four_ai.c [ai_calc_move]: prio[%d]: %d\n", i, prio[i]);
    }
    for (unsigned char cur_dep = depth - 1;
        cur_dep >= 0; cur_dep--) {
        for (unsigned char i = 0; i < COLUMNS; i++) {
            debug_print(
                DEBUG_AI_1, "four_ai.c [ai_calc_move]: loosing[%d]: %d\n",
                prio[i], loosing[cur_dep][prio[i]]);
            // This condition is true true if and only if the move does not
            // lead to a loosing situation (unless not preventable that other
            // player wins in next move) and the move is valid.
            if ((!loosing[cur_dep][prio[i]] ||
                (cur_dep == 0 && def_loosing[cur_dep])) &&
                exec_move(g, prio[i])) {
                revert_move(g, prio[i]);
                return prio[i];
            }
        }
    }
    // This should never be reached.
    return 0;
}

// ____________________________________
unsigned char winning(game_state *g, unsigned char depth) {
    for (unsigned char i = 0; i < 50 - depth; i++) {
        debug_print(DEBUG_AI_REC_1, "%s", " ");
    }
    debug_print(DEBUG_AI_1,
        "four_ai.c [winning]: winning called with depth %d\n", depth);
    char game_over_var = game_over(g);
    if (game_over_var != 0 || depth == 0) {
        if (game_over_var == -1) return 0;
        debug_print(DEBUG_AI_1, "four_ai.c [winning]: End of recursion, "
            "depth: %d, game_over: %d\n\n", depth, game_over_var);
        debug_print(DEBUG_AI_REC_1, "x%d\n", game_over_var);
        return game_over_var;
    }
    bool not_to_move = true;
    for (unsigned char j = 0; j < COLUMNS; j++) {
        unsigned char prev_to_move = g->to_move;
        if (exec_move(g, j)) {
            debug_print(DEBUG_AI_2,
                "four_ai.c [winning]: Current column: %d\n", j);
            debug_print(DEBUG_AI_REC_1, "%d\n", j);
            if (DEBUG_AI_3) {
                output_to_stream(stderr, g, FORMAT_READABLE);
            }
            // One winning path is enough to win.
            unsigned char winning_player = winning(g, depth - 1);

            if (winning_player == prev_to_move) {
                revert_move(g, j);
                debug_print(DEBUG_AI_1,
                    "four_ai.c [winning]: depth: %d\n", depth);
                debug_print(DEBUG_AI_1, "four_ai.c [winning]: winning path "
                    "found for player %d\n", prev_to_move);
                return prev_to_move;
            } else if (winning_player == g->to_move) {
                // not_to_move = true;
                // (HERE IS THE PROBLEM!!!!!!!!!!!!!!)
                debug_print(DEBUG_AI_1, "four_ai.c [winning]: possible "
                    "winning path found for player %d\n", g->to_move);
            } else {
                not_to_move = false;
            }
            revert_move(g, j);
        }
    }
    // This is only reached if the player to move is not able to win on its own
    debug_print(DEBUG_AI_1, "four_ai.c [winning]: depth: %d\n", depth);
    if (not_to_move) {
        unsigned char player =
            g->to_move == PLAYER_A_NUM ? PLAYER_B_NUM : PLAYER_A_NUM;
        debug_print(DEBUG_AI_1, "four_ai.c [winning]: winning path "
            "found for player %d\n", player);
        return player;
    } else {
        debug_print(
            DEBUG_AI_1, "four_ai.c [winning]: no winning path found %s\n", "");
        return 0;
    }
}
