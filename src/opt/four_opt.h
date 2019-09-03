// Copyright 2019 Nils Kober
// Author: Nils Kober <nils.kober@students.uni-freiburg.de>
// Published under MIT License

#ifndef SRC_OPT_FOUR_OPT_H_
#define SRC_OPT_FOUR_OPT_H_

#include <stdbool.h>

typedef struct four_opt_t {
    bool help;
    bool ai;
    char *input;
    unsigned char diff;
} four_opt;

/* Read all valid options in the given string array
(where argc is the size of this argv) and write them into flags */
void read_opt(int argc, char *argv[], four_opt *flags);

#endif  // SRC_OPT_FOUR_OPT_H_
