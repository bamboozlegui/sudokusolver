#include <stdio.h>

void readFile(int grid[][9], char file[]) {
    FILE *data;
    data = fopen(file, "r");
    for(int row, col, i = 0; i < 81; ++i) {
        row = i / 9;
        col = i % 9;

        grid[row][col] = getc(data) - 48;
        getc(data); // skip the SPACE
    }
}

void printTable(int grid[][9]) {
    printf("SUDOKU TABLE: \n");
    for(int row, col, i = 0; i < 81; ++i) {
        row = i / 9;
        col = i % 9;
        if( i % 9 == 0) {
            printf("\n");
        }
        printf("%d ", grid[row][col]);
    }
    printf("\n\n");
}

// checks if there's space available
int checkForEmptySpace(int grid[][9], int* row, int* col) {
    for(int i = 0; i < 9; ++i) {
        for(int j = 0; j < 9; ++j) {
            if(grid[i][j] == 0) {
                *row = i;
                *col = j;
                return 1;
            }
        }
    }

    return 0;
}

// check row and collumn for collisions
int checkRowAndCol(int grid[][9], int row, int col, int num) {
    for(int i = 0; i < 9; ++i) {
        if( (grid[row][i] == num) || (grid[i][col] == num) )
            return 0;
    }

    return 1;
}

// check 3x3 subgrid for collisions
int checkSubGrid(int grid[][9], int row, int col, int num) {
    int r,c;
    r = row - (row % 3);
    c = col - (col % 3);

    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            if(grid[r + i][c + j] == num) {
                return 0;
            }
        }
    }

    return 1;
}

int solver(int grid[][9], int row, int col) {
    // if space check returns 0, sudoku has been solved 
    if(checkForEmptySpace(grid, &row, &col) == 0) {
        return 1;
    }

    for(int number = 1; number < 10; ++number) {
        if(checkRowAndCol(grid, row, col, number) != 0 && checkSubGrid(grid, row, col, number) != 0) {
            grid[row][col] = number;

        if(solver(grid, row, col) == 1) { 
            return 1;
        }

        grid[row][col] = 0;
        }
    }
    
    // if there's no number available, start backtracking
    return 0;
}


int main(int argc, char *argv[]) {
    int sudoku[9][9];
    readFile(sudoku, "sudoku1.txt");
    printf("Find solution for ");
    printTable(sudoku);

    if(solver(sudoku, 0, 0) == 1) {
        printf("\nSolved ");
        printTable(sudoku);
    }

    return 0;
}