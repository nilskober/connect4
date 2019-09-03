// Copyright 2019 Nils Kober
// Author: Nils Kober <nils.kober@students.uni-freiburg.de>
// Published under MIT License

#ifndef SRC_DEBUG_FOUR_DEBUG_H_
#define SRC_DEBUG_FOUR_DEBUG_H_
#define debug_print(module, format, ...) \
            do { \
                if (module) fprintf(stderr, format, __VA_ARGS__); \
            } while (0)

#define DEBUG_TEST_HELPER_1 0
#define DEBUG_IO_1 0
#define DEBUG_GAME_1 0
#define DEBUG_GAME_2 0
#define DEBUG_AI_1 0
#define DEBUG_AI_2 0
#define DEBUG_AI_3 0
#define DEBUG_AI_REC_1 0
#define DEBUG_MAIN_1 0




#include <stdio.h>

#endif  // SRC_DEBUG_FOUR_DEBUG_H_
