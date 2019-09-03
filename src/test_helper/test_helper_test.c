// Copyright 2019 Nils Kober
// Author: Nils Kober <nils.kober@students.uni-freiburg.de>
// Published under MIT License

#include <assert.h>
#include <stdio.h>
#include "test_helper.h"

#define TEST_FILES "./testFiles/files_equal/"


void filesEqual_bothEmpty_true();
void filesEqual_nonEmptyBothEqual_true();
void filesEqual_equalLengthDifferentContent_false();
void filesEqual_differentLegthSamePrefix_false();

int main(void) {
    fprintf(stderr, "\n");
    filesEqual_bothEmpty_true();
    filesEqual_nonEmptyBothEqual_true();
    filesEqual_equalLengthDifferentContent_false();
    filesEqual_differentLegthSamePrefix_false();
    return 0;
}

void filesEqual_bothEmpty_true() {
    const char f[] = TEST_FILES"empty_01.txt";
    const char g[] = TEST_FILES"empty_02.txt";
    assert(files_equal(f, g));
}

void filesEqual_nonEmptyBothEqual_true() {
    const char f[] = TEST_FILES"nonEmptyEqual_01.txt";
    const char g[] = TEST_FILES"nonEmptyEqual_02.txt";
    assert(files_equal(f, g));
}

void filesEqual_equalLengthDifferentContent_false() {
    const char f[] = TEST_FILES"equalLengthDifferentContent_01.txt";
    const char g[] = TEST_FILES"equalLengthDifferentContent_02.txt";
    assert(!files_equal(f, g));
}

void filesEqual_differentLegthSamePrefix_false() {
    const char f[] = TEST_FILES"differentLegthSamePrefix_01.txt";
    const char g[] = TEST_FILES"differentLegthSamePrefix_02.txt";
    assert(!files_equal(f, g));
}
