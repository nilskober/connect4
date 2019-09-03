// Copyright 2019 Nils Kober
// Author: Nils Kober <nils.kober@students.uni-freiburg.de>
// Published under MIT License

#ifndef SRC_GAME_FOUR_GAME_H_
#define SRC_GAME_FOUR_GAME_H_

#define LINES 6
#define COLUMNS 7
#define MATCH_LEN 4


#define EMPTY_NUM 0
#define PLAYER_A_NUM 1
#define PLAYER_B_NUM 2

#define MAX_DEPTH 42  // max search depth for ai

#include <stdbool.h>


typedef struct game_state_t {
    // Game matrix.
    unsigned char arr[LINES][COLUMNS];
    // Current number of counters in the given column.
    unsigned char current_line[COLUMNS];
    // Player who moves next.
    unsigned char to_move;
} game_state;

/* Initialize the given instance of game_state.
Set all elements of arr to 0.
Set to_move to PLAYER_A_NUM. */
void game_state_init(game_state *game);

/* Execute the given move. That means a counter for the player to move will be
inserted in the given column. If the move is illegal (e.g. the column is
full or does not exist) false will be returned, otherwise true.
The first column will be number 0. */
bool exec_move(game_state *g, unsigned char column);

/* Remove the top-most counter in the given column (if there is one).
Due to performance optimization, this function does not return any error
if input is invalid. */
void revert_move(game_state *g, unsigned char column);

/* Check if the current game_state respresents the end of the game.
Return: 0               if not game over
        PLAYER_A_NUM    if Player A has won
        PLAYER_B_NUM    if Player B has won
        -1              in case of a draw */
char game_over(game_state *g);

/* Start the command line based version of connect four.
If ai == true, one plays against the computer.
If input != NULL, the file from the given path will be loaded.
diff is search depth for the ai. */
void run(bool ai, const char input[], unsigned char diff);

/* Check the given position (i, j) in the given game matrix and modify the
counters accordingly.
If player A has won, return PLAYER_A_NUM; if player B has won, return PLAYER_B_NUM.
Otherwise return 0. */
static inline unsigned char counter_helper(
    game_state *g, unsigned char i, unsigned char j, unsigned char *counter_a,
    unsigned char *counter_b, bool *empty) {
    if (g->arr[i][j] == EMPTY_NUM) {
                *counter_a = 0;
                *counter_b = 0;
                *empty = true;
            } else if (g->arr[i][j] == PLAYER_A_NUM) {
                (*counter_a)++;
                *counter_b = 0;
            } else {
                (*counter_b)++;
                *counter_a = 0;
            }
            if (*counter_a == MATCH_LEN) {
                return PLAYER_A_NUM;
            } else if (*counter_b == MATCH_LEN) {
                return PLAYER_B_NUM;
            } else {
                return 0;
            }
}

#endif  // SRC_GAME_FOUR_GAME_H_
