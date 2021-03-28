#include <stdio.h>

int nums[] = {0,1,2,3,4,5,6,7,8,9};

void readFile(int grid[9][9]) {
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
}

// checks if there's space available
void checkForEmptySpace(int grid[][9], int* row, int* col) {
    while(grid[*row][*col] != 0 && (*row)*(*col) != 81) {
        if(*col == 9) {
            ++(*row);
            *col = 0;        
        }
        ++(*col);
    }
}

int checkRowAndCol(int grid[][9], int row, int col, int num) {

    for(int i = 0; i < 9; ++i) { // patikrina eilute
        if(grid[row][i] == num)
            return 0;
    }

    //-------------------------------------------------------
    for(int i = 0; i < 9; ++i) { // patikrina eilute
        if(grid[row][i] == num)
            return 0;
    }

    for(int i = 0; i < 9; ++i) { // patikrina stulpeli
        if(grid[i][col] == num) 
            return 0;
    }

    return 1;
}

int checkSubGrid(int grid[][9], int row, int col, int num) { // patikrina 3x3 kvadrata
    int r,c;
    r = row / 3;
    c = col / 3;
    for(int i = 0; i < 9; ++i) {
        if(i % 3 == 0) {

        }
        if(grid[r][c] == num) ;
        // if()
    } 
}

int solver(int grid[][9], int row, int col) {
    // irasyt skaiciu, check for collisions, go back jei randa collisions
    
    checkForEmptySpace(grid, &row, &col);
    if(row*col == 64) {
        return 1;
    }

    for(int number = 1; number < 10; ++number) {
        if((checkRowAndCol(grid, row, col, number) && checkSubGrid(grid, row, col, number) ) != 0) {
            grid[row][col] == number;
            
        }
        else {
            return 
        }
    }
    if(grid[row][col] == 0) {


    };
}


int main(int argc, char *argv[]) {
    int sudoku[9][9]; 
    readFile(sudoku);
    // printTable(sudoku);
    int row = 0, col = 0;
    checkForEmptySpace(sudoku, &row, &col);
    printf("%d %d", row, col);
    // solveSudoku(sudoku, 0, 0)
    return 0;
}




/*{
    {'x', '4', 'x', '8', 'x', 'x', 'x', 'x', '5'},
    {'5', 'x', 'x', 'x', 'x', '2', 'x', 'x', 'x'},
    {'x', '2', '7', 'x', '4', 'x', 'x', 'x', '1'},
    {'x', 'x', 'x', 'x', '5', 'x', '8', '2', 'x'},
    {'2', 'x', '8', '3', '9', '6', 'x', 'x', '4'},
    {'7', 'x', 'x', 'x', '8', '4', '1', '6', 'x'},
    {'1', 'x', '5', 'x', '6', 'x', '4', '9', 'x'},
    {'9', 'x', '2', 'x', 'x', 'x', '3', 'x', '7'},
    {'3', '7', 'x', '9', 'x', '8', '5', '1', 'x'}

};*/

