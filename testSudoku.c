#include "testSudoku.h" // To access included files and runTests() definition.

/*===========================================================================*/
/*===== Testing Variables ===================================================*/
/*===========================================================================*/

/*======== Return Value Variable ===*/
int rv;


/*======== Grid Variables ===*/

// an empty grid.
sudokuGrid testGrid;

// for checking legality of moves with invalidating '1's.
sudokuGrid validGrid = {
    '.','.','.',   '.','.','.',   '.','.','1',
    '1','.','.',   '.','1','.',   '.','.','.',
    '.','.','.',   '.','.','.',   '.','.','.',

    '.','.','.',   '.','.','.',   '.','.','.',
    '.','.','.',   '.','.','.',   '.','.','.',
    '.','.','.',   '.','.','.',   '.','.','.',

    '.','.','.',   '.','.','.',   '.','.','.',
    '.','.','.',   '.','.','.',   '.','.','.',
    '.','.','.',   '.','.','.',   '.','.','.',
};

// filled with valid chars and no blanks.
sudokuGrid validFullGrid = {
    '1','2','3',   '4','5','6',   '7','8','9',
    '1','2','3',   '4','5','6',   '7','8','9',
    '1','2','3',   '4','5','6',   '7','8','9',

    '1','2','3',   '4','5','6',   '7','8','9',
    '1','2','3',   '4','5','6',   '7','8','9',
    '1','2','3',   '4','5','6',   '7','8','9',

    '1','2','3',   '4','5','6',   '7','8','9',
    '1','2','3',   '4','5','6',   '7','8','9',
    '1','2','3',   '4','5','6',   '7','8','9',
};

// has bad char 'X'.
sudokuGrid badCharGrid = {
    '1','2','3',   '4','5','6',   '7','X','9',
    '1','2','3',   '4','5','6',   '7','X','9',
    '1','2','3',   '4','5','6',   '7','X','9',

    '1','2','3',   '4','5','6',   '7','X','9',
    '1','2','3',   '4','5','6',   '7','X','9',
    '1','2','3',   '4','5','6',   '7','X','9',

    '1','2','3',   '4','5','6',   '7','X','9',
    '1','2','3',   '4','5','6',   '7','X','9',
    '1','2','3',   '4','5','6',   '7','X','9',
};

// too short.
sudokuGrid badLengthGrid = {
    '1','2','3',   '4','5','6',   '7','8','9',
    '1','2','3',   '4','5','6',   '7','8','9',
    '1','2','3',   '4','5','6',   '7','8','9',

    '1','2','3',   '4','5','6',   '7','8','9',
    '1','2','3',   '4','5','6',   '7','8','9',
    '1','2','3',   '4','5','6',   '7','8','9',

    '1','2','3',   '4','5','6',   '7','8','9',
    '1','2','3',   '4','5','6',   '7','8','9',
    '1','2','3',   '4','5','6',   '7',
};



/*============================================================================*/
/*===== Static Test Functions. ===============================================*/
/*============================================================================*/

static void testReadGrid() {

    // Test reading with a valid grid.
    rv = readGrid(testGrid, validGrid);

    assert(rv);
    assert(strlen(testGrid) == GRID_SIZE);
    assert(strcmp(testGrid, validGrid) == 0);


    // Test reading a grid with bad values.
    rv = readGrid(testGrid, badCharGrid);
    assert(!rv);


    // Test reading a grid that is the wrong length.
    rv = readGrid(testGrid, badLengthGrid);
    assert(!rv);
}

static void testIsFull() {

    // Test a grid with BLANK values (not full).
    rv = isFull(validGrid);
    assert(!rv);

    // Test a grid that is full.
    rv = isFull(validFullGrid);
    assert(rv);
}

static void testGetBlankCell() {

    // Test a grid with blank cells.
    rv = getBlankCell(validGrid);
    assert(validGrid[rv] == BLANK);


    // Test a grid that doesn't have blank cells.
    rv = getBlankCell(validFullGrid);
    assert(rv == -1);
}

static void testIsLegal() {

    // Test a value that is in the same row.
    rv = isLegal(validGrid, 1, '1'); // Same row, same value.
    assert(!rv);

    rv = isLegal(validGrid, 1, '9'); // Same row, different value.
    assert(rv);


    // Test a value that is in the same column.
    rv = isLegal(validGrid, 18, '1'); // Same column, same value.
    assert(!rv);

    rv = isLegal(validGrid, 18, '9'); // Same column, different value.
    assert(rv);


    // Test a value that is in the same sub-grid.
    rv = isLegal(validGrid, 21, '1'); // Same sub-grid, same value.
    assert(!rv);

    rv = isLegal(validGrid, 21, '9'); // Same sub-grid, different value.
    assert(rv);


    // Test a valid move with no column, row, or sub-grid relation.
    rv = isLegal(validGrid, 29, '9'); // A valid move, good value.
    assert(rv);

    rv = isLegal(validGrid, 29, 'X'); // A valid move, bad value.
    assert(!rv);
}

static void testSetCell() {
    cell target = 2;
    value valid = '9';
    value invalid = 'X';

    // Test a valid cell assignment.
    rv = setCell(validGrid, target, valid);
    assert(rv);
    assert(validGrid[target] == valid);


    // Test an invalid cell assignment.
    rv = setCell(validGrid, target, invalid);
    assert(!rv);
}

static void testClearCell() {
    cell target, invalidTarget;
    target = 2;
    invalidTarget = 100;

    // Test a index that is valid.
    rv = clearCell(validGrid, target); // index exists.
    assert(rv);
    assert(validGrid[target] == BLANK);


    // Test an invalid index.
    rv = clearCell(validGrid, invalidTarget); // index is not in sudokuGrid.
    assert(!rv);
}

static void testPrintGrid() {

    // Test printing a grid with BLANK values.
    rv = printGrid(validGrid);
    assert(rv);


    // Test printing a full, valid grid.
    rv = printGrid(validFullGrid);
    assert(rv);


    // Test printing a grid with invalid values.
    rv = printGrid(badCharGrid);
    assert(!rv);


    // Test printing a grid with invalid length.
    rv = printGrid(badLengthGrid);
    assert(!rv);
}



/*============================================================================*/
/*===== Run Tests Function. ==================================================*/
/*============================================================================*/

void runTests() {

    // Announce what is being tested.
    printf("Testing sudoku.c ...");

    // Run tests.
    testReadGrid();
    testIsFull();
    testGetBlankCell();
    testIsLegal();
    testSetCell();
    testClearCell();
    testPrintGrid();


    // Print that all tests passed.
    printf("All tests passed!");
}

