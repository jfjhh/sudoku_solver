#include "sudoku.h" // To access included files and runTests() definition.

/*===========================================================================*/
/*===== Static Helper Functions. ============================================*/
/*===========================================================================*/

/*======== getSubGrid Base Helper ===*/

static cell getSubGridBase(cell loc) {
    // get the first cell in the subGrid -- which is ridiculously hard to do.

    cell base, baseRow;

    // get the first cell in the row of the subGrid containing loc by
    // subtracting the offset from the start of the row from loc, yeilding the
    // cell at the start of the subGrid row.
    baseRow = ( loc - (loc % GRID_SUB_LENGTH));

    /**************************************************************************
     * Calculate the base (first cell) in a subGrid.
     * This is VERY complicated to do without an ADT, and even harder to do
     * with a single-dimensional array of values.
     *
     * The 'columns' of subGrids for understanding are identified as follows:
     *
     * The first are the leftmost three subGrids,
     * The second are the center three subGrids,
     * The third are the rightmost three subGrids.
     *
     * Upon modding (%) the column of subGrids by GRID_CHUNK,
     * The first yeilds 0,
     * The second yeilds 3,
     * The third yeilds 6.
     * === This gives us the column of the subGrid.
     *
     * Upon comparing to see if the cell, whose grid membership is undefined,
     * we can see the subGrid column with simiple inequalities.
     * The first: loc < GRID_CHUNK.
     * The second: loc < (GRID_CHUNK * 2)
     * The third: loc < (GRID_CHUNK * 3)
     * === This gives us the row of the subGrid.
     *
     * By combining the column and the row, the subGrid is determined, through
     * too many if-statements.
     *************************************************************************/

    if (baseRow % GRID_CHUNK == 0) { // 1c valid.
        base = baseRow;

    } else if ((baseRow - (GRID_LENGTH * 2)) % GRID_CHUNK == 0) { // 1c 2r up.
        base = (baseRow - (GRID_LENGTH * 2));

    } else if ((baseRow - GRID_LENGTH) % GRID_CHUNK == 0) { // 1c 1r up.
        base = (baseRow - GRID_LENGTH);

    } else if ((baseRow + GRID_LENGTH) % GRID_CHUNK == 0) { // 1c 1r down.
        base = (baseRow + GRID_LENGTH);

    } else if (baseRow % GRID_CHUNK == 3) { // 2c valid.
        base = baseRow;

    } else if ((baseRow - (GRID_LENGTH * 2)) % GRID_CHUNK == 3) { // 2c 2r up.
        base = (baseRow - (GRID_LENGTH * 2));

    } else if ((baseRow - GRID_LENGTH) % GRID_CHUNK == 3) { // 2c 1r up.
        base = (baseRow - GRID_LENGTH);

    } else if ((baseRow + GRID_LENGTH) % GRID_CHUNK == 3) { // 2c 1r down.
        base = (baseRow + GRID_LENGTH);

    } else if (baseRow % GRID_CHUNK == 6) { // 3c valid.
        base = baseRow;

    } else if ((baseRow - (GRID_LENGTH * 2)) % GRID_CHUNK == 6) { // 3c 2r up.
        base = (baseRow - (GRID_LENGTH * 2));

    } else if ((baseRow - GRID_LENGTH) % GRID_CHUNK == 6) { // 3c 1r up.
        base = (baseRow - GRID_LENGTH);

    } else if ((baseRow + GRID_LENGTH) % GRID_CHUNK == 6) { // 3c 1r down.
        base = (baseRow + GRID_LENGTH);

    } else { // unable to compute base. should never happen...
        printf("BAD BASE!");
        base = 0;
    }

    return base;
}

/*======== Get Group Functions for isLegal() ===*/

static void getColumns(group columns, cell loc) {
    cell i, base;

    // get base (offset from the beginning of the row).
    if (loc < GRID_LENGTH) {
        // when between 0 and before GRID_LENGTH, its already a base.
        base = loc;
    } else {
        // when after first row, must calculate offset from GRID_LENGTH with
        // modulus (%) to get the base.
        base = (loc % GRID_LENGTH);
    }

    // iterate for GRID_LENGTH, adding an offset number of the rows down
    // to the base, to get all the cells in the column.
    for (i = 0; i < GRID_LENGTH; i++) {
        columns[i] = (base + (GRID_LENGTH * i)); // => the base + rows down.
    }
}

static void getRows(group rows, cell loc) {
    cell i, base;

    // get base (first cell in row).
    base = (loc - (loc % GRID_LENGTH));

    // iterate through row, assigning values offset from the row.
    for (i = 0; i < GRID_LENGTH; i++) {
        rows[i] = (base + i);
    }
}

static void getSubGrid(group subGrid, cell loc) {
    cell i, j, index, base;

    index = 0;
    base = getSubGridBase(loc);

    // assign the cells to subGrid.
    for (i = 0; i < GRID_CHUNK; i += GRID_LENGTH) { // 0..9..18..END.
        for (j = 0; j < GRID_SUB_LENGTH; j++) { // 0..1..2..END.

            // calculate the subGrid index and assign it.
            subGrid[index] = (base + i + j);

            index++; // move to the next index for assignment.
        }
    }

}


/*======== Check Legal Group Sub-Functions for isLegal() ===*/

static int isLegalGroup(sudokuGrid game, group validationGroup,
        cell targetCell, value moveValue) {
    // can assume that parameters have been validated.

    int i, j;
    // value gameValue, searchValue;
    value searchValue;
    cell searchIndex;

    // Iterate and check if the targetCell is a cell of the group.
    for (i = 0; i < GRID_LENGTH; i++) {
        // gameValue = game[validationGroup[i]];

        // Cell is in group.
        if (validationGroup[i] == targetCell) {

            // Iterate through the group cells again.
            for (j = 0; j < GRID_LENGTH; j++) {
                searchIndex = validationGroup[j];
                searchValue = game[searchIndex];

                // If any value of the cells in the group match the moveValue,
                // then the move is not legal.
                if (searchValue == moveValue) {
                    return FALSE;
                }
            }

        }
    }

    // Fallthrough, the group is valid.
    return TRUE;
}

static int isLegalColumn(sudokuGrid game, cell targetCell, value moveValue) {
    // can assume that parameters have been validated.

    int legal;
    group columns;

    // get the columns of the cell.
    getColumns(columns, targetCell);

    // check the group move is legal.
    legal = isLegalGroup(game, columns, targetCell, moveValue);

    // return the legality of the columns.
    return legal;
}

static int isLegalRow(sudokuGrid game, cell targetCell, value moveValue) {
    // can assume that parameters have been validated.

    int legal;
    group rows;

    // get the columns of the cell.
    getRows(rows, targetCell);

    // check the group move is legal.
    legal = isLegalGroup(game, rows, targetCell, moveValue);

    // return the legality of the rows.
    return legal;
}

static int isLegalSubGrid(sudokuGrid game, cell targetCell, value moveValue) {
    // can assume that parameters have been validated.

    int legal;
    group subGrid;

    // get the columns of the cell.
    getSubGrid(subGrid, targetCell);

    // check the group move is legal.
    legal = isLegalGroup(game, subGrid, targetCell, moveValue);

    // return the legality of the subGrid.
    return legal;
}



/*===========================================================================*/
/*===== Public Functions. ===================================================*/
/*===========================================================================*/

/*======== Major Functions ===*/

int readGrid(sudokuGrid game, sudokuGrid inGrid) {

    // check grid is valid.
    if (!isValid(inGrid))
        return FALSE;

    // copy the inputted grid to the grid to be solved.
    strcpy(game, inGrid);

    // return, based on the validity of the read game.
    return TRUE;
}

int readGridFromConsole(sudokuGrid game) {
    cell i, j;                                  // iteration variables.
    value inGrid [GRID_LENGTH + 1] = {0};       // a row.
    value temp [(GRID_LENGTH * 2) - 1] = {0};   // a row with whitespace and \n

    // print a prompt.
    printf("+=== ENTER A SUDOKU GRID: ===+\n");
    printf("+=== 9 CELLS, SEPARATED BY SPACES; ===+\n");
    printf("+=== PRESS ENTER TO GO TO THE NEXT ROW. ===+\n\n");
    printf("+-----+---------------------+\n");
    printf("|  #  |  1 2 3 4 5 6 7 8 9  |\n");
    printf("+-----+---------------------+\n");

    // read the grid from the terminal, row by row.
    for (i = 0; i < GRID_LENGTH; i++) {

        // get the grid row with formatting spaces from the user.
        printf("|  %d  |  ", i + 1); // a prompt.
        fgets(temp, (GRID_LENGTH * 2) + 1, stdin);

        // null-terminate ('\0') the string if it ends with a newline.
        if (temp [strlen(temp) - 1] == '\n')
            temp [strlen(temp) - 1] = '\0';

        // iterate over every other char, thus skipping spaces.
        for (j = 0; j < (GRID_LENGTH * 2); j += 2)
            inGrid[j / 2] = temp[j]; // assign the values, without whitespace.

        // concat the row to the game.
        strncat(game, inGrid, (size_t) GRID_LENGTH);
    }
    printf("+-----+---------------------+\n"); // end of grid table.

    // validate grid.
    if (!isValid(game))
        return FALSE;

    // return, based on the validity of the read game.
    return TRUE;
}

int isLegal(sudokuGrid game, cell targetCell, value moveValue) {
    // check if the game and moveValue are even valid first.
    if ((isValid(game)) && (isValidValue(moveValue))) {
        if (isLegalColumn(game, targetCell, moveValue)) {
            if (isLegalRow(game, targetCell, moveValue)) {
                if (isLegalSubGrid(game, targetCell, moveValue)) {
                    return TRUE;
                }
            }
        }
    }

    return FALSE; // Fallthrough to here if anything is non-legal.
}

int printGrid(sudokuGrid game) {
    // be sure the grid is valid.
    if (isValid(game)) {

        value num;
        cell i, j, index;
        index = 0;

        // vertical spacing.
        printf("\n");

        // iterate over rows.
        for (j=0; j < GRID_LENGTH; j++) {

            // iterate over columns.
            for (i=0; i < GRID_LENGTH; i++, index++) {

                // the value at the current index of the grid.
                num = game[index];

                // value is at end of sub-grid, add space to make distinct.
                if (((i + 1) % GRID_SUB_LENGTH) == 0 && (i != 0))
                    printf("%2c   ", num);
                else
                    printf("%2c ", num);
            }

            // row is at tne of sub-grid, add vertical space to make distinct.
            if (((j + 1) % GRID_SUB_LENGTH == 0) && (j != 0))
                printf("\n\n");
            else
                printf("\n");
        }

        // all printed correctly.
        return TRUE;
    } else {

        // grid was not valid, so could not be printed.
        return FALSE;
    }
}


/*======== Validation Functions ===*/

int isValidValue(value testValue) {
    // if testValue is not between chars '1' to '9'.
    if (!((testValue <= MAX_VALUE) && (testValue >= MIN_VALUE))) {

        // ... and it is not BLANK.
        if (!(testValue == BLANK))

            // Then it must be invalid.
            return FALSE;
    }

    // Otherwise, testValue is valid.
    return TRUE;
}

int isValid(sudokuGrid game) {
    int i;

    // iterate over the whole grid.
    for (i = 0; i < GRID_SIZE; i++) {

        // check if the value in the grid is valid.
        if (!isValidValue(game[i]))
            return FALSE;
    }

    // check if the string is the right size.
    if (strlen(game) == GRID_SIZE)
        return TRUE;
    else
        return FALSE;
}


/*======== Helper Cell and Grid Functions ===*/

int isFull(sudokuGrid game) {
    // iterate through the grid, check for BLANK.
    int i;
    for (i = 0; i < GRID_SIZE; i++) {
        if (game[i] == BLANK) {
            return FALSE;
        }
    }

    // if no blanks, then the grid is full.
    return TRUE;
}

int setCell(sudokuGrid game, cell targetCell, value moveValue) {
    // validate the move cell.
    if ((targetCell < GRID_SIZE) && (targetCell >= 0)) {

        // validate the move value.
        if (isValidValue(moveValue)) {

            value before, after;

            // assign the cell, and check the outcome to be ok.
            before = game[targetCell];
            game[targetCell] = moveValue;
            after = game[targetCell];

            // be sure that there was a change in values.
            if (before != after)
                return TRUE;
        }

    }
    // Fallthrough, bad values or no change comes here.
    return FALSE;
}

int clearCell(sudokuGrid game, cell targetCell) {
    // check the value at the cell is good, therefore check that the cell
    // is a valid cell.
    if (isValidValue(game[targetCell])) {

        int ok;

        // set the cell to be BLANK.
        ok = setCell(game, targetCell, BLANK);
        if (ok) {
            return TRUE;
        }
    }

    // Fallthrough, bad cell/value and bad assignment come here.
    return FALSE;
}

cell getBlankCell(sudokuGrid game) {
    // iterate through the grid and get the first cell that is BLANK.
    int i;
    for (i = 0; i < GRID_SIZE; i++) {
        if (game[i] == BLANK) {
            return i;
        }
    }

    // on no blank cell, return -1 (1 could be a cell).
    return -1;
}

