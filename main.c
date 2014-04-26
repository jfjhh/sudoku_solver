#include <stdio.h>          // To printf().
#include "sudoku.h"         // To use sudoku functions.
#include "testSudoku.h"     // To run unit tests.


// Prints grid if solveable, or 'no solution' if it has no solution,
// Returns TRUE or FALSE based on success.
int hasSolution(sudokuGrid game);

/*=== Main: Solve a Grid. ===*/
int main(int argc, const char *argv[]) {

    /*=======================*/
    /*=== Run Unit Tests. ===*/
    /*=======================*/

    // runTests(); // Unit tests.
    // printf("\n*******************************\n");


    /*=====================*/
    /*=== Grid solving. ===*/
    /*=====================*/

    sudokuGrid game = {0};
    int ok;

    // read the grid into game.
    if (argc == 1) {
        ok = readGridFromConsole(game);

    } else if (argc == 2) {
        ok = readGrid(game, (value *)argv[1]);

    } else {
        ok = FALSE;
    }

    // check that reading was successful.
    if (!ok) {
        // an error message.
        printf("\n");
        printf("+=== OOPS! THE READING OF THE GRID WAS UNSUCCESSFUL. ===+\n");
        printf("+=== PLEASE TRY AGAIN. ===+\n");

        return 2;
    }

    // check if the grid has a solution.
    if (hasSolution(game)) {

        // the grid has a solution.
        printf("\n"); // Vertical spacing.
        printf("+=== The Grid's Solution: ===+\n");

        // print the solved grid to the teminal, check ok.
        ok = printGrid(game);
        assert(ok);

        return 0;

    } else {

        // print that the grid has no solution.
        printf("\n"); // Vertical spacing.
        printf("+=== The Grid Has No Solution. ===+\n");
        printf("+=== I was able to solve up to this point: ===+\n");

        // print the unsolved grid to the teminal, check ok.
        ok = printGrid(game);
        assert(ok);

        return 1;
    }
}


/*=== Function hasSolution(). ===*/
int hasSolution(sudokuGrid game) {
    // the grid has already been validated in the read.

    int solved;

    // if it's already full, then it's already solved.
    if (isFull(game)) {
        solved = TRUE;
    } else {
        cell candidateCell;
        value trialValue;

        solved = FALSE; // the grid is not solved yet.
        candidateCell = getBlankCell(game); // Any blank cell.
        assert(candidateCell != -1); // check there was a blank cell assigned.
        trialValue = MIN_VALUE; // starting value, will incrument later.

        // check that the grid isn't solved, and that there are other possible
        // answers to check with trialValue.
        while ((!solved) && (trialValue <= MAX_VALUE)) {

            // be sure the move is legal.
            if (isLegal(game, candidateCell, trialValue)) {
                int ok;

                // set the cell to the legal value and check if this is ok.
                ok = setCell(game, candidateCell, trialValue);
                assert(ok);

                // check if this new grid has a solution with recursivity.
                // if this doesn't work out, clear the cell and backtrack.
                if (hasSolution(game)) {
                    solved = TRUE; // the grid is solved.

                } else {
                    ok = clearCell(game, candidateCell);
                    assert(ok);
                }
            }

            trialValue++; // move to the next trial value.
        }
    }

    // returns based on if the grid has a solution or not.
    return solved;
}

