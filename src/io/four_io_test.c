// Copyright 2019 Nils Kober
// Author: Nils Kober <nils.kober@students.uni-freiburg.de>
// Published under MIT License

#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include "four_io.h"
#include "./../game/four_game.h"
#include "./../test_helper/test_helper.h"

#define TEST_FILES "./testFiles/io/"

/*
Notes:
It is sufficient to test output_to_file because all other functions also just
use output_to_stream, which is also used by output_to_file.
*/

void output_emptyMatrixFormatNone_fileCotainsOnlySpaces();
void output_nonEmptyMatrixFormatMachine_fileCotainsCorrectSymbols();
void output_nonEmptyMatrixFormatReadable_fileCotainsCorrectSymbols();
void output_wrongNumbersInMatrixFormatNone_emptySymbolForWrongNumbers();

void readFile_emptyFile_falseAndGameInit();
void readFile_prevSavedFile_trueSameStateAsBeforeSaving();

int main(void) {
    fprintf(stderr, "\n");
    output_emptyMatrixFormatNone_fileCotainsOnlySpaces();
    output_nonEmptyMatrixFormatMachine_fileCotainsCorrectSymbols();
    output_nonEmptyMatrixFormatReadable_fileCotainsCorrectSymbols();
    output_wrongNumbersInMatrixFormatNone_emptySymbolForWrongNumbers();

    readFile_emptyFile_falseAndGameInit();
    readFile_prevSavedFile_trueSameStateAsBeforeSaving();
    return 0;
}

void output_emptyMatrixFormatNone_fileCotainsOnlySpaces() {
    game_state game;
    game_state_init(&game);
    output_to_file("temp.txt", &game, FORMAT_NONE);
    assert(files_equal("temp.txt", TEST_FILES"fileCotainsOnlySpaces.txt"));
    unlink("temp.txt");
}

void output_nonEmptyMatrixFormatMachine_fileCotainsCorrectSymbols() {
    game_state game;
    game_state_init(&game);
    game.arr[0][0] = PLAYER_A_NUM;
    game.arr[5][6] = PLAYER_B_NUM;
    game.arr[2][2] = PLAYER_A_NUM;
    output_to_file("temp.txt", &game, FORMAT_MACHINE);
    assert(files_equal("temp.txt",
        TEST_FILES"fileCotainsCorrectSymbolsForMachine.txt"));
    unlink("temp.txt");
}

void output_nonEmptyMatrixFormatReadable_fileCotainsCorrectSymbols() {
    game_state game;
    game_state_init(&game);
    game.arr[0][0] = PLAYER_A_NUM;
    game.arr[5][6] = PLAYER_B_NUM;
    game.arr[2][2] = PLAYER_A_NUM;
    output_to_file("temp.txt", &game, FORMAT_READABLE);
    assert(files_equal("temp.txt",
        TEST_FILES"fileCotainsCorrectSymbolsForReadable.txt"));
    unlink("temp.txt");
}

void output_wrongNumbersInMatrixFormatNone_emptySymbolForWrongNumbers() {
    game_state game;
    game_state_init(&game);
    game.arr[0][0] = PLAYER_A_NUM;
    game.arr[5][6] = 5;
    game.arr[2][2] = 8;
    output_to_file("temp.txt", &game, FORMAT_NONE);
    assert(files_equal("temp.txt",
        TEST_FILES"emptySymbolForWrongNumbers.txt"));
    unlink("temp.txt");
}

void readFile_emptyFile_falseAndGameInit() {
    game_state g;
    g.arr[0][0] = 1;
    assert(!read_file(TEST_FILES"emptyFile.txt", &g));
    assert(g.arr[0][0] == EMPTY_NUM);
}

void readFile_prevSavedFile_trueSameStateAsBeforeSaving() {
    game_state g;
    game_state_init(&g);
    exec_move(&g, 0);  // A
    exec_move(&g, 0);  // B
    exec_move(&g, 1);  // A
    exec_move(&g, 2);  // B
    exec_move(&g, 3);  // A
    exec_move(&g, 4);  // B
    exec_move(&g, 5);  // A
    exec_move(&g, 6);  // B
    exec_move(&g, 4);  // A

    save("temp.txt", &g);
    game_state f;
    read_file("temp.txt", &f);
    assert(g.to_move == f.to_move);
    for (int j = 0; j < COLUMNS; j++) {
        for (int i = 0; i < LINES; i++) {
            assert(g.arr[i][j] == f.arr[i][j]);
        }
        assert(g.current_line[j] == f.current_line[j]);
    }
    unlink("temp.txt");
}
