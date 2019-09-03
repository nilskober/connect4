// Copyright 2019 Nils Kober
// Author: Nils Kober <nils.kober@students.uni-freiburg.de>
// Published under MIT License

#include <stdio.h>
#include "./../debug/four_debug.h"
#include "test_helper.h"

// ____________________________________
bool files_equal(const char f_name[], const char g_name[]) {
    FILE *f = fopen(f_name, "rb");
    FILE *g = fopen(g_name, "rb");
    if (!f || !g) {
        debug_print(DEBUG_TEST_HELPER_1, "test_helper.c [files_equal]: %s or "
            "%s could not be read.\n", f_name, g_name);
        debug_print(DEBUG_TEST_HELPER_1, "test_helper.c [files_equal]: "
            "pointer f: %p, pointer g: %p\n", (void *)f, (void *)g);

        return false;
    }
    char c_f;
    char c_g;
    do {
        c_f = fgetc(f);
        c_g = fgetc(g);
    } while (c_f == c_g && c_f != EOF);
    debug_print(DEBUG_TEST_HELPER_1, "test_helper.c [files_equal]: At end of "
        "loop: c_f: %d,\t c_g: %d\n", c_f, c_g);
    bool res = (c_f == c_g);

    fclose(f);
    fclose(g);
    return res;
}
