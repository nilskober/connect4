// Copyright 2019 Nils Kober
// Author: Nils Kober <nils.kober@students.uni-freiburg.de>
// Published under MIT License

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "four_io.h"
#include "./../game/four_game.h"
#include "./../debug/four_debug.h"

// ____________________________________
void output_to_stream(FILE *f, game_state *game, unsigned char mode) {
    if (mode == FORMAT_READABLE) {
        fputc('\n', f);
    }
    for (int i = LINES - 1; i > -1; i--) {
        if (mode == FORMAT_READABLE) {
            fputc('\t', f);
        }
        for (int j = 0; j < COLUMNS; j++) {
            if (mode == FORMAT_READABLE) {
                fputc('|', f);
            }
            if (game->arr[i][j] == PLAYER_A_NUM) {
                fputc(PLAYER_A_SYMBOL, f);
            } else if (game->arr[i][j] == PLAYER_B_NUM) {
                fputc(PLAYER_B_SYMBOL, f);
            } else {
                fputc(EMPTY_SYMBOL, f);
            }
        }
        if (mode == FORMAT_READABLE) {
            fputc('|', f);
        }
        fputc('\n', f);
    }
    if (mode == FORMAT_READABLE) {
        fputc('\t', f);
        for (unsigned char i = 1; i < COLUMNS + 1; i++) {
            fputs("--", f);
        }
        fputs("-\n", f);
        fputc('\t', f);
        for (unsigned char i = 1; i < COLUMNS + 1; i++) {
            fprintf(f, " %d", i);
        }
        fputc('\n', f);
        if (game->to_move == PLAYER_A_NUM) {
            fputs("\nPlayer A (*)", f);
        } else if (game->to_move == PLAYER_B_NUM) {
            fputs("\nPlayer B (o)", f);
        }
    } else if (mode == FORMAT_MACHINE) {
        fputc(game->to_move == PLAYER_A_NUM ?
            PLAYER_A_SYMBOL : PLAYER_B_SYMBOL, f);
    }
}

// ____________________________________
bool output_to_file(const char f_name[], game_state *game, unsigned char mode) {
    FILE *f = fopen(f_name, "wb");
    if (!f) {
        debug_print(DEBUG_IO_1, "four_io.c [output_to_file]: "
            "%s could not be read.\n", f_name);
        return false;
    }
    output_to_stream(f, game, mode);
    fclose(f);
    debug_print(DEBUG_IO_1, "four_io.c [output_to_file]: "
        "%s successfully written.\n", f_name);
    return true;
}

// ____________________________________
void output(game_state *game) {
    output_to_stream(stdout, game, FORMAT_READABLE);
}

// ____________________________________
bool save(const char f_name[], game_state *game) {
    return output_to_file(f_name, game, FORMAT_MACHINE);
}

// ____________________________________
bool read_file(const char f_name[], game_state *g) {
    FILE *f = fopen(f_name, "rb");
    bool failure = false;
    if (!f) {
        debug_print(DEBUG_IO_1,
                    "four_io.c [read]: %s: File could not be read.\n", f_name);
        failure = true;
    }
    for (unsigned char i = 0; i < COLUMNS; i++) {
        g->current_line[i] = LINES;
    }
    if (!failure) {
        for (int i = LINES - 1; i >= 0; i--) {
            for (int j = 0; j < COLUMNS; j++) {
                char ch = fgetc(f);
                if (ch == PLAYER_A_SYMBOL) {
                    g->arr[i][j] = PLAYER_A_NUM;
                } else if (ch == PLAYER_B_SYMBOL) {
                    g->arr[i][j] = PLAYER_B_NUM;
                } else {
                    g->arr[i][j] = EMPTY_NUM;
                    g->current_line[j] = i;
                }
            }
            if (fgetc(f) != '\n') {
                debug_print(DEBUG_IO_1, "four_io.c [read]: "
                    "%s: no line break in line %d\n", f_name, LINES - i);
                failure = true;
            }
        }
        char ch = fgetc(f);
        if (ch == PLAYER_A_SYMBOL) {
            g->to_move = PLAYER_A_NUM;
        } else if (ch == PLAYER_B_SYMBOL) {
            g->to_move = PLAYER_B_NUM;
        } else {
            debug_print(DEBUG_IO_1, "four_io.c [read]: "
                "%s: no player to move, char: %d, %c\n", f_name, ch, ch);
            failure = true;
        }
    }
    fclose(f);
    if (failure) {
        game_state_init(g);
    }
    return !failure;
}

// ____________________________________
unsigned char read_number() {
    int res;
    #define BUFSIZE 10
    char buffer[BUFSIZE];
    fgets(buffer, BUFSIZE, stdin);
    res = (int) strtol(buffer, 0, 10);
    while (res < 1 || res > COLUMNS) {
        printf("%s\n%s", "Invalid input!", "Enter column: ");
        fgets(buffer, BUFSIZE, stdin);
        res = (int) strtol(buffer, 0, 10);
    }
    return (unsigned char) res;
}
