// Copyright 2019 Nils Kober
// Author: Nils Kober <nils.kober@students.uni-freiburg.de>
// Published under MIT License

#include <stdio.h>
#include "four_game.h"
#include "./../io/four_io.h"
#include "./../debug/four_debug.h"
#include "./../ai/four_ai.h"

// ____________________________________
void game_state_init(game_state *game) {
    for (int i = 0; i < LINES; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            game->arr[i][j] = 0;
        }
    }
    for (int i = 0; i < COLUMNS; i++) {
        game->current_line[i] = 0;
    }
    game->to_move = PLAYER_A_NUM;
}

// ____________________________________
bool exec_move(game_state *g, unsigned char column) {
    // Check if column is valid.
    if (column >= COLUMNS) {
        debug_print(DEBUG_GAME_1, "four_game.c [exec_move]: "
            "Column %d is invalid (does not exist).\n", column);
        return false;
    }
    if (g->current_line[column] >= LINES) {
        debug_print(DEBUG_GAME_1, "four_game.c [exec_move]: "
            "Column %d is invalid (already full).\n", column);
        return false;
    }

    // Now column is valid.
    unsigned char cl = g->current_line[column];
    if (g->to_move == PLAYER_A_NUM) {
        g->arr[cl][column] = PLAYER_A_NUM;
        g->to_move = PLAYER_B_NUM;
    } else {
        g->arr[cl][column] = PLAYER_B_NUM;
        g->to_move = PLAYER_A_NUM;
    }
    g->current_line[column]++;

    debug_print(DEBUG_GAME_1, "four_game.c [exec_move]: "
            "Added counter to column %d.\n", column);

    return true;
}

// ____________________________________
char game_over(game_state *g) {
    debug_print(DEBUG_GAME_2, "%s\n\n", "");
    // Will be set to true if any empty entry found.
    bool empty = false;
    unsigned char counter_a = 0;
    unsigned char counter_b = 0;

    // Go line by line, check for horizontal matches.
    for (unsigned char i = 0; i < LINES; i++) {
        for (unsigned char j = 0; j < COLUMNS - MATCH_LEN + 1 ||
                ((counter_a > 0 || counter_b > 0) && j < COLUMNS); j++) {
            unsigned char res = counter_helper(
                g, i, j, &counter_a, &counter_b, &empty);

            debug_print(DEBUG_GAME_2, "four_game.c [game_over]: horizontal "
                "\tcolumn: %d, line: %d, counter_a: %d, counter_b: %d.\n",
                j, i, counter_a, counter_b);

            if (res) {
                return res;
            }
        }
        counter_a = 0;
        counter_b = 0;
        debug_print(DEBUG_GAME_2, "%s\n", "");
    }

    // Go column by column, check for vertical matches.
    for (unsigned char j = 0; j < COLUMNS; j++) {
        for (unsigned char i = 0; i < LINES - MATCH_LEN + 1 ||
                ((counter_a > 0 || counter_b > 0) && i < LINES); i++) {
            unsigned char res = counter_helper(
                g, i, j, &counter_a, &counter_b, &empty);

            debug_print(DEBUG_GAME_2, "four_game.c [game_over]: vertical "
                "\tcolumn: %d, line: %d, counter_a: %d, counter_b: %d.\n",
                j, i, counter_a, counter_b);

            if (res) {
                return res;
            }
        }
        counter_a = 0;
        counter_b = 0;
        debug_print(DEBUG_GAME_2, "%s\n", "");
    }

    // Check for diagonal matches from top left to bottom right.
    // --> iterate over sum of coordinates
    unsigned char min_sum = MATCH_LEN -1;
    unsigned char max_sum = LINES + COLUMNS - MATCH_LEN - 1;
    for (unsigned char sum = min_sum; sum < max_sum + 1; sum++) {
        for (unsigned char i = 0; i < sum + 1 && i < LINES; i++) {
            unsigned char j = sum - i;  // Will always be non-negative
            if (j >= COLUMNS) continue;
            unsigned char res = counter_helper(
                g, i, j, &counter_a, &counter_b, &empty);

            debug_print(DEBUG_GAME_2, "four_game.c [game_over]: diagonal "
                "(same sum) \tcolumn: %d, line: %d, counter_a: %d, "
                "counter_b: %d.\n", j, i, counter_a, counter_b);

            if (res) {
                return res;
            }
        }
        counter_a = 0;
        counter_b = 0;
        debug_print(DEBUG_GAME_2, "%s\n", "");
    }

    // Check for diagonal matches from bottom left to top right.
    // --> iterate over difference of coordinates
    char min_diff = - (LINES < COLUMNS ? LINES : COLUMNS) + MATCH_LEN;
    char max_diff = (LINES < COLUMNS ? COLUMNS : LINES) - MATCH_LEN;
    for (char diff = min_diff; diff < max_diff + 1; diff++) {
        debug_print(DEBUG_GAME_2, "diff: %d\n", diff);
        for (unsigned char i = 0; i < LINES && i < COLUMNS - diff; i++) {
            // j will always be non-negative
            char signed_j = i + diff;
            if (signed_j < 0) continue;
            unsigned char j = (unsigned char) signed_j;
            unsigned char res = counter_helper(
                g, i, j, &counter_a, &counter_b, &empty);

            debug_print(DEBUG_GAME_2, "four_game.c [game_over]: diagonal "
                "(same diff) \tcolumn: %d, line: %d, counter_a: %d, "
                "counter_b: %d.\n", j, i, counter_a, counter_b);

            if (res) {
                return res;
            }
        }
        counter_a = 0;
        counter_b = 0;
        debug_print(DEBUG_GAME_2, "%s\n", "");
    }

    if (empty) {
        return 0;  // Game not finished.
    } else {
        return -1;  // Draw.
    }
}

// ____________________________________
void run(bool ai, const char input[], unsigned char diff) {
    // Preperations
    game_state g;
    if (input != NULL) {
        read_file(input, &g);
    } else {
        game_state_init(&g);
    }
    unsigned char ai_player = 0;
    printf("\n\n%s\n\n", "********** Connect 4 **********");
    if (ai) {
        printf("%s\n", "Artificial intelligence activated.");
        printf("%s", "Would you like to start (y/n)?\n");
        char ch = fgetc(stdin);
        while (ch != 'y' && ch != 'n') {
            printf("\n%s\n", "Invalid input!");
            printf("%s", "Would you like to start (y/n)?\n");
            ch = fgetc(stdin);
        }
        if (ch == 'y') {
            ai_player = PLAYER_B_NUM;
        } else {
            ai_player = PLAYER_A_NUM;
        }
        while (ch != '\n') {
            ch = fgetc(stdin);
        }
    }
    char res = 0;
    while (!res) {
        output(&g);
        if (ai && g.to_move == ai_player) {
            int col = ai_calc_move(&g, diff);
            exec_move(&g, col);
            printf(" has chosen column %d.\n", col + 1);
        } else {
            printf("%s\n", ", enter column (or 's' to save): ");
            char ch = fgetc(stdin);
            if (ch == 's') {
                fgetc(stdin);  // Remove the '\n'
                printf("\nYou have chosen to save the game."
                    "\nEnter name of file: \n");
                char buffer[1024];
                int i = 0;
                while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
                    buffer[i] = ch;
                    i++;
                }
                buffer[i] = '\0';
                bool saved = save(buffer, &g);
                if (saved) {
                    printf("%s\n", "File saved.");
                } else {
                    printf("%s\n", "File could not be saved.");
                }
                return;
            }
            ungetc(ch, stdin);
            unsigned char col = read_number();
            col--;  // Internally column 1 is at index 0
            if (!exec_move(&g, col)) {
                printf("%s\n%s", "Invalid input!", "Enter column: ");
            }
        }
        res = game_over(&g);

        if (res == PLAYER_A_NUM) {
            g.to_move = 0;
            output_to_stream(stdout, &g, FORMAT_READABLE);
            printf("\n%s\n\n\n", "******* Player A has won *******");
        } else if (res == PLAYER_B_NUM) {
            g.to_move = 0;
            output_to_stream(stdout, &g, FORMAT_READABLE);
            printf("\n%s\n\n\n", "******* Player B has won *******");
        } else if (res == -1) {
            g.to_move = 0;
            output_to_stream(stdout, &g, FORMAT_READABLE);
            printf("\n%s\n\n\n", "******* Draw *******");
        }
    }
}

// ____________________________________
void revert_move(game_state *g, unsigned char column) {
    g->arr[g->current_line[column] - 1][column] = 0;
    g->to_move = g->to_move == PLAYER_A_NUM ? PLAYER_B_NUM : PLAYER_A_NUM;
    g->current_line[column]--;
}
