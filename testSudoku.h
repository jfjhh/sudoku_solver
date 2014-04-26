/*=== Include Guard ===*/
#ifndef TESTSUDOKU_H
#define TESTSUDOKU_H


/*=== Includes ===*/

#include "sudoku.h"     // To use sudoku functions.
#include <assert.h>     // To test everything.
#include <string.h>     // To do string operations in tests.


/*=== Function Declarations ===*/

// Runs all unit tests for sudoku.c, and will abort the program if a test
// does not pass. All tests are defined as static in "testSudoku.c".
void runTests();

#endif

