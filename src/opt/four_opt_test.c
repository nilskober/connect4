// Copyright 2019 Nils Kober
// Author: Nils Kober <nils.kober@students.uni-freiburg.de>
// Published under MIT License

#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "four_opt.h"

void readOpt_help_helpTrueOthersFalseOrNULL();
void readOpt_ai_aiTrueOthersFalseOrNULL();
void readOpt_input_inputAssignedOthersFalse();
void readOpt_diff_diffAssignedOthersFalse();
void readOpt_helpAiInput_allTrueOrAssigned();
void readOpt_none_allFalseOrNULL();



int main(void) {
    readOpt_help_helpTrueOthersFalseOrNULL();
    readOpt_ai_aiTrueOthersFalseOrNULL();
    readOpt_input_inputAssignedOthersFalse();
    readOpt_diff_diffAssignedOthersFalse();
    readOpt_helpAiInput_allTrueOrAssigned();
    readOpt_none_allFalseOrNULL();
    return 0;
}

void readOpt_help_helpTrueOthersFalseOrNULL() {
    int argc = 2;
    char *argv[] = {"./4", "--help"};
    four_opt flags;
    read_opt(argc, argv, &flags);
    assert(flags.help == true);
    assert(flags.ai == false);
    assert(flags.input == NULL);
    assert(flags.diff == 0);
}

void readOpt_ai_aiTrueOthersFalseOrNULL() {
    int argc = 2;
    char *argv[] = {"./4", "--ai"};
    four_opt flags;
    read_opt(argc, argv, &flags);
    assert(flags.help == false);
    assert(flags.ai == true);
    assert(flags.input == NULL);
    assert(flags.diff == 0);
}

void readOpt_input_inputAssignedOthersFalse() {
    int argc = 3;
    char *argv[] = {"./4", "--input", "testFile.txt"};
    four_opt flags;
    read_opt(argc, argv, &flags);
    assert(flags.help == false);
    assert(flags.ai == false);
    assert(strcmp(flags.input, "testFile.txt") == 0);
    assert(flags.diff == 0);
}

void readOpt_diff_diffAssignedOthersFalse() {
    int argc = 3;
    char *argv[] = {"./4", "--diff", "5"};
    four_opt flags;
    read_opt(argc, argv, &flags);
    assert(flags.help == false);
    assert(flags.ai == false);
    assert(flags.input == NULL);
    assert(flags.diff == 5);
}

void readOpt_helpAiInput_allTrueOrAssigned() {
    int argc = 7;
    char *argv[] = {
        "./4", "--input", "testFile.txt", "--help", "--ai", "--diff", "5"};
    four_opt flags;
    read_opt(argc, argv, &flags);
    assert(flags.help == true);
    assert(flags.ai == true);
    assert(strcmp(flags.input, "testFile.txt") == 0);
    assert(flags.diff == 5);
}

void readOpt_none_allFalseOrNULL() {
    int argc = 1;
    char *argv[] = {"./4"};
    four_opt flags;
    read_opt(argc, argv, &flags);
    assert(flags.help == false);
    assert(flags.ai == false);
    assert(flags.input == NULL);
    assert(flags.diff == 0);
}
