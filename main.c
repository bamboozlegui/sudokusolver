#include <stdio.h>

int nums[] = {0,1,2,3,4,5,6,7,8,9};

void readFile(int grid[][9]) {
    FILE *data;
    data = fopen("sudoku1.txt", "r");
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

int checkRowAndCol(int grid[][9], int row, int col, int num) {

    for(int i = 0; i < 9; ++i) { // check the row for collisions
        if( (grid[row][i] == num) || (grid[i][col] == num) )
            return 0;
    }

    return 1;
}

int checkSubGrid(int grid[][9], int row, int col, int num) { // check 3x3 subgrid for collisions
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
int callnum = 1;

int solver(int grid[][9], int row, int col) {
    // irasyt skaiciu, check for collisions, go back jei randa collisions
    // printf("call number: %d\n", callnum++);
    // printf("table number %d:\n", callnum++);
    // printTable(grid);sleep(1);


    if(checkForEmptySpace(grid, &row, &col) == 0) { 
        printf("\nSOLVED!!!!!!!!!!!!!\n");
        return 1;   // solved!
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
    // jei loop neranda tinkamo skaiciaus

    return 0;
}


int main(int argc, char *argv[]) {
    int sudoku[9][9]; 
    readFile(sudoku);
    int row = 0, col = 0;
    // checkForEmptySpace(sudoku, &row, &col);
    // printf("%d %d, returns: %d", row, col, checkForEmptySpace(sudoku, &row, &col));
    printf("%d", solver(sudoku, 0, 0));
    
    // for(int number = 1; number < 10; ++number) {
    //     if(checkRowAndCol(sudoku, row, col, number) == 1 && checkSubGrid(sudoku, row, col,  number) == 1) {
    //         printf("row: %d |---| col: %d |----| num: %d, no colllision? %d \n", row, col, number, checkRowAndCol(sudoku, row, col, number));
    //         sudoku[row][col] = number;
    //         printf("%d\n", sudoku[row][col]);
    //     }
        
    // }

    printTable(sudoku);

    
    return 0;
}