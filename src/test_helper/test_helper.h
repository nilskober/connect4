// Copyright 2019 Nils Kober
// Author: Nils Kober <nils.kober@students.uni-freiburg.de>
// Published under MIT License

#ifndef SRC_TEST_HELPER_TEST_HELPER_H_
#define SRC_TEST_HELPER_TEST_HELPER_H_

#include <stdbool.h>

/* Return true if both of the given files (not their names) are equal.
Otherweise return false.
Return false in case any files could not be read. */
bool files_equal(const char f_name[], const char g_name[]);

#endif  // SRC_TEST_HELPER_TEST_HELPER_H_
