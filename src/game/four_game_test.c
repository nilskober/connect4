// Copyright 2019 Nils Kober
// Author: Nils Kober <nils.kober@students.uni-freiburg.de>
// Published under MIT License

#include <assert.h>
#include "four_game.h"

void gameStateInit_noValuesAssigned_matrixWithOnlyZeroToMoveA();
void gameStateInit_nonZeroMatrixToMoveBLinesNotZero_\
matrixWithOnlyZeroToMoveA();

void execMove_allColumnsEmpty_trueNewCounterAdded();
void execMove_givenColumnEmpty_trueNewCounterAdded();
void execMove_givenColumnFull_false();
void execMove_givenColumnOutOfRange_false();

void revertMove_legalInput_deleteCounter();

void gameOver_allEmpty_0();
void gameOver_playerAWinsLine_PlayerA();
void gameOver_playerBWinsLine_PlayerB();
void gameOver_playerAWinsColumn_PlayerA();
void gameOver_playerAWinsDiagonalSumLowest_PlayerA();
void gameOver_playerAWinsDiagonalSumHighest_PlayerA();
void gameOver_playerAWinsDiagonalDiffLowest_PlayerA();
void gameOver_playerAWinsDiagonalDiffHighest_PlayerA();
void gameOver_4InARowButWithLineBreakInBetween_0();

void gameOver_nonEmptyNoWinner_draw();



int main(void) {
    gameStateInit_noValuesAssigned_matrixWithOnlyZeroToMoveA();
    gameStateInit_nonZeroMatrixToMoveBLinesNotZero_matrixWithOnlyZeroToMoveA();

    execMove_allColumnsEmpty_trueNewCounterAdded();
    execMove_givenColumnEmpty_trueNewCounterAdded();
    execMove_givenColumnFull_false();
    execMove_givenColumnOutOfRange_false();

    revertMove_legalInput_deleteCounter();

    gameOver_allEmpty_0();
    gameOver_playerAWinsLine_PlayerA();
    gameOver_playerBWinsLine_PlayerB();
    gameOver_playerAWinsColumn_PlayerA();
    gameOver_playerAWinsDiagonalSumLowest_PlayerA();
    gameOver_playerAWinsDiagonalSumHighest_PlayerA();
    gameOver_playerAWinsDiagonalDiffLowest_PlayerA();
    gameOver_playerAWinsDiagonalDiffHighest_PlayerA();
    gameOver_4InARowButWithLineBreakInBetween_0();

    return 0;
}

void gameStateInit_noValuesAssigned_matrixWithOnlyZeroToMoveA() {
    game_state game;
    game_state_init(&game);
    // TEST: All arr elements are 0.
    for (int i = 0; i < LINES; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            assert(game.arr[i][j] == 0);
        }
    }
    // TEST: to_move is PLAYER_A_NUM.
    assert(game.to_move == PLAYER_A_NUM);

    // TEST: all entries in current_line are 0.
    for (int i = 0; i < COLUMNS; i++) {
        assert(game.current_line[i] == 0);
    }
}

void gameStateInit_nonZeroMatrixToMoveBLinesNotZero_\
matrixWithOnlyZeroToMoveA() {
    game_state game;
    game.arr[0][0] = 1;
    game.current_line[4] = 1;
    game.to_move = PLAYER_B_NUM;
    game_state_init(&game);
    // TEST: All arr elements are 0.
    for (int i = 0; i < LINES; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            assert(game.arr[i][j] == 0);
        }
    }
    // TEST: to_move is PLAYER_A_NUM
    assert(game.to_move == PLAYER_A_NUM);

    // TEST: all entries in current_line are 0.
    for (int i = 0; i < COLUMNS; i++) {
        assert(game.current_line[i] == 0);
    }
}

void execMove_allColumnsEmpty_trueNewCounterAdded() {
    game_state g;
    game_state_init(&g);
    assert(exec_move(&g, 3));
    assert(g.to_move == PLAYER_B_NUM);
    assert(g.arr[0][3] == PLAYER_A_NUM);
    assert(g.current_line[3] == 1);
}

void execMove_givenColumnEmpty_trueNewCounterAdded() {
    game_state g;
    game_state_init(&g);
    assert(exec_move(&g, 3));
    assert(g.to_move == PLAYER_B_NUM);
    assert(g.arr[0][3] == PLAYER_A_NUM);
    assert(g.current_line[3] == 1);
}

void execMove_givenColumnFull_false() {
    game_state g;
    game_state_init(&g);
    g.current_line[3] = LINES;
    g.arr[LINES - 1][3] = PLAYER_B_NUM;
    assert(!exec_move(&g, 3));
    assert(g.to_move == PLAYER_A_NUM);
    assert(g.arr[LINES - 1][3] == PLAYER_B_NUM);
    assert(g.current_line[3] == LINES);
}

void execMove_givenColumnOutOfRange_false() {
    game_state g;
    game_state_init(&g);
    assert(!exec_move(&g, COLUMNS));
    assert(g.to_move == PLAYER_A_NUM);
}

void gameOver_allEmpty_0() {
    game_state g;
    game_state_init(&g);
    assert(!game_over(&g));
}

void revertMove_legalInput_deleteCounter() {
    game_state g;
    game_state_init(&g);
    exec_move(&g, 1);
    exec_move(&g, 2);
    exec_move(&g, 2);
    revert_move(&g, 2);
    assert(g.to_move == PLAYER_A_NUM);
    assert(g.arr[1][2] == 0);
    assert(g.current_line[2] == 1);
}

void gameOver_playerAWinsLine_PlayerA() {
    game_state g;
    game_state_init(&g);
    g.arr[1][1] = PLAYER_A_NUM;
    g.arr[1][2] = PLAYER_A_NUM;
    g.arr[1][3] = PLAYER_A_NUM;
    g.arr[1][4] = PLAYER_A_NUM;
    g.arr[0][4] = PLAYER_A_NUM;

    g.arr[0][3] = PLAYER_B_NUM;
    g.arr[0][2] = PLAYER_B_NUM;
    g.arr[0][1] = PLAYER_B_NUM;
    g.arr[0][5] = PLAYER_B_NUM;
    g.arr[1][5] = PLAYER_B_NUM;
    // --> A has 4 in a row in a line

    assert(game_over(&g) == PLAYER_A_NUM);
}

void gameOver_playerBWinsLine_PlayerB() {
    game_state g;
    game_state_init(&g);
    g.arr[1][1] = PLAYER_B_NUM;
    g.arr[1][2] = PLAYER_B_NUM;
    g.arr[1][3] = PLAYER_B_NUM;
    g.arr[1][4] = PLAYER_B_NUM;
    g.arr[0][4] = PLAYER_B_NUM;

    g.arr[0][3] = PLAYER_A_NUM;
    g.arr[0][2] = PLAYER_A_NUM;
    g.arr[0][1] = PLAYER_A_NUM;
    g.arr[0][5] = PLAYER_A_NUM;
    g.arr[1][5] = PLAYER_A_NUM;
    // --> B has 4 in a row in a line

    assert(game_over(&g) == PLAYER_B_NUM);
}

void gameOver_playerAWinsColumn_PlayerA() {
    // Same example as test for line, but matrix is tranposed.
    game_state g;
    game_state_init(&g);
    g.arr[1][1] = PLAYER_A_NUM;
    g.arr[2][1] = PLAYER_A_NUM;
    g.arr[3][1] = PLAYER_A_NUM;
    g.arr[4][1] = PLAYER_A_NUM;
    g.arr[4][0] = PLAYER_A_NUM;

    g.arr[3][0] = PLAYER_B_NUM;
    g.arr[2][0] = PLAYER_B_NUM;
    g.arr[1][0] = PLAYER_B_NUM;
    g.arr[5][0] = PLAYER_B_NUM;
    g.arr[5][1] = PLAYER_B_NUM;
    // --> A has 4 in a row in a column

    assert(game_over(&g) == PLAYER_A_NUM);
}

void gameOver_playerAWinsDiagonalSumLowest_PlayerA() {
    game_state g;
    game_state_init(&g);

    g.arr[3][0] = PLAYER_A_NUM;
    g.arr[2][1] = PLAYER_A_NUM;
    g.arr[1][2] = PLAYER_A_NUM;
    g.arr[0][3] = PLAYER_A_NUM;

    g.arr[5][3] = PLAYER_B_NUM;
    g.arr[0][2] = PLAYER_B_NUM;
    g.arr[2][2] = PLAYER_B_NUM;
    g.arr[0][4] = PLAYER_B_NUM;

    assert(game_over(&g) == PLAYER_A_NUM);
}

void gameOver_playerAWinsDiagonalSumHighest_PlayerA() {
    game_state g;
    game_state_init(&g);

    g.arr[2][6] = PLAYER_A_NUM;
    g.arr[3][5] = PLAYER_A_NUM;
    g.arr[4][4] = PLAYER_A_NUM;
    g.arr[5][3] = PLAYER_A_NUM;

    g.arr[5][2] = PLAYER_B_NUM;
    g.arr[0][2] = PLAYER_B_NUM;
    g.arr[2][2] = PLAYER_B_NUM;
    g.arr[0][4] = PLAYER_B_NUM;

    assert(game_over(&g) == PLAYER_A_NUM);
}

void gameOver_playerAWinsDiagonalDiffLowest_PlayerA() {
    game_state g;
    game_state_init(&g);

    g.arr[2][0] = PLAYER_A_NUM;
    g.arr[3][1] = PLAYER_A_NUM;
    g.arr[4][2] = PLAYER_A_NUM;
    g.arr[5][3] = PLAYER_A_NUM;

    g.arr[5][2] = PLAYER_B_NUM;
    g.arr[0][2] = PLAYER_B_NUM;
    g.arr[2][2] = PLAYER_B_NUM;
    g.arr[0][4] = PLAYER_B_NUM;

    assert(game_over(&g) == PLAYER_A_NUM);
}

void gameOver_playerAWinsDiagonalDiffHighest_PlayerA() {
    game_state g;
    game_state_init(&g);

    g.arr[0][3] = PLAYER_A_NUM;
    g.arr[1][4] = PLAYER_A_NUM;
    g.arr[2][5] = PLAYER_A_NUM;
    g.arr[3][6] = PLAYER_A_NUM;

    g.arr[5][2] = PLAYER_B_NUM;
    g.arr[0][2] = PLAYER_B_NUM;
    g.arr[2][2] = PLAYER_B_NUM;
    g.arr[0][4] = PLAYER_B_NUM;

    assert(game_over(&g) == PLAYER_A_NUM);
}

void gameOver_4InARowButWithLineBreakInBetween_0() {
    game_state g;
    game_state_init(&g);
    g.arr[1][0] = PLAYER_A_NUM;
    g.arr[0][4] = PLAYER_A_NUM;
    g.arr[0][5] = PLAYER_A_NUM;
    g.arr[0][6] = PLAYER_A_NUM;

    assert(game_over(&g) == 0);
}
