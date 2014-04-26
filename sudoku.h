/*=== Include Guard ===*/
#ifndef SUDOKU_H
#define SUDOKU_H


/*=== Includes ===*/

#include <assert.h>     // To assert pre and post conditions.
#include <string.h>     // To do string operations like strlen() and strcmp().
#include <stdio.h>      // To use input/output from/to the terminal.


/*=== Defines ===*/

#define TRUE 1          // Boolean true.
#define FALSE 0         // Boolean false.

#define MIN_VALUE '1'   // Minimum value for a sudokuGrid.
#define MAX_VALUE '9'   // Maximum value for a sudokuGrid.
#define BLANK '.'       // The character to be used for an undefined value.

#define GRID_LENGTH 9   // The side length of a grid.
#define GRID_SIZE (GRID_LENGTH * GRID_LENGTH) // The number of cells in a grid.
#define GRID_CHUNK (GRID_LENGTH * (GRID_LENGTH / 3)) // The distance from the top to the bottom of a subGrid.
#define GRID_SUB_LENGTH (GRID_LENGTH / 3) // The length of a subGrid.


/*=== Typedefs ===*/

typedef char value;                     // A value of a grid.
typedef int cell;                       // An index in the grid.
typedef cell group[GRID_LENGTH];        // A column, row, or sub-grid of cells.
typedef value sudokuGrid[GRID_SIZE];    // A sudoku grid of concrete dimensions.


/*=== Function Declarations ===*/

// Reads from inGrid to game, while checking that values passed are valid in
// a sudokuGrid and that the grid ends up the correct length.
// Returns TRUE or FALSE based on success.
int readGrid(sudokuGrid game, sudokuGrid inGrid);

// Reads a grid from the console, while checking that values passed are
// valid in a sudokuGrid and that the grid ends up the correct length.
// Returns TRUE or FALSE based on success.
int readGridFromConsole(sudokuGrid game);

// Returns TRUE or FALSE depending if a grid has any BLANK characters in it.
int isFull(sudokuGrid game);

// Returns a cell with BLANK from the grid.
cell getBlankCell(sudokuGrid game);

// Checks that the move in the grid, at the cell, with the value, is valid
// in a sudoku grid.
// Returns TRUE or FALSE based on success.
int isLegal(sudokuGrid game, cell targetCell, value moveValue);

// Sets a cell in a game, to a value, whilst checking that the value is a
// valid value in a sudoku grid.
// Returns TRUE or FALSE based on success.
int setCell(sudokuGrid game, cell targetCell, value moveValue);

// Sets a cell in a game, to BLANK, while checking that the cell passed to it
// is valid, and checking that the assignment was successful.
// Returns TRUE or FALSE based on success.
int clearCell(sudokuGrid game, cell targetCell);

// Checks that a grid is valid, then prints it to the terminal, formatted with
// spaces and newlines, to look like a sudoku grid, with sub-grid seperation.
// Returns TRUE or FALSE based on success.
int printGrid(sudokuGrid game);

// Checks that a grid is valid, checking all its cells, and then if the grid
// length is proper.
// Returns TRUE or FALSE based on validity.
int isValid(sudokuGrid game);

// Checks that a value is valid, checking it against all values between
// MIN_VALUE and MAX_VALUE, as well as checking BLANK.
// Returns TRUE or FALSE based on validity.
int isValidValue(value testValue);

#endif

