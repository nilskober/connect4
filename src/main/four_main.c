/*
This is a simple, command line based implementation of the game connect four.

Copyright 2019 Nils Kober
Author: Nils Kober <nils.kober@students.uni-freiburg.de>
Published under MIT License
*/

#include <stddef.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include "./../ai/four_ai.h"
#include "./../man/four_man.h"
#include "./../game/four_game.h"
#include "./../opt/four_opt.h"
#include "./../debug/four_debug.h"

int main(int argc, char *argv[]) {
    four_opt flags;
    read_opt(argc, argv, &flags);
    if (flags.help) {
        printf("%s\n", manual);
    } else {
        if (flags.diff == 0) {
            flags.diff = AI_DEFAULT_DIFF;
        } else if (flags.diff > 42) {
            printf("Invalid difficulty. Set search depth to deafult.\n");
            flags.diff = AI_DEFAULT_DIFF;
        } else if (flags.diff > 6) {
            printf("WARNING: Search depth greater than 6 may lead to slow "
                "performance.\n");
        }
        struct timeval t;
        gettimeofday(&t, 0);
        debug_print(DEBUG_MAIN_1,
            "four_main.c [main]: srand init long: %ld\n", t.tv_sec);
        debug_print(DEBUG_MAIN_1, "four_main.c [main]: "
            "srand init uint: %d\n", (unsigned int) t.tv_sec);
        srand((unsigned int) t.tv_sec);
        run(flags.ai, flags.input, flags.diff);
    }
    return 0;
}
