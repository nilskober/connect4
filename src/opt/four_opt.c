// Copyright 2019 Nils Kober
// Author: Nils Kober <nils.kober@students.uni-freiburg.de>
// Published under MIT License

#include <getopt.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "four_opt.h"

struct option opt[] = {
  {"help", no_argument, NULL, 'h'},
  {"ai", no_argument, NULL, 'a'},
  {"input", required_argument, NULL, 'i'},
  {"diff", required_argument, NULL, 'd'},  // difficulty of ai
  {NULL, 0, NULL, 0}
};
void read_opt(int argc, char *argv[], four_opt *flags) {
    // init
    flags->help = false;
    flags->ai = false;
    flags->input = NULL;
    flags->diff = 0;
    // process options
    optind = 1;
    char ch = getopt_long(argc, argv, "hai:d:", opt, NULL);
    while (ch != -1) {
        switch (ch) {
            case 'h':
                flags->help = true;
                break;
            case 'a':
                flags->ai = true;
                break;
            case 'i':
                flags->input = optarg;
                break;
            case 'd':
                errno = 0;
                flags->diff = (unsigned char) strtol(optarg, 0, 10);
                if (errno) {
                    printf("Invalid argument type for --diff. "
                        "Set difficulty to default value.\n");
                }
        }
        ch = getopt_long(argc, argv, "hai:d:", opt, NULL);
    }
}
