#include "solver.h"
#include <iostream>
#define LOG(x) std::cout << x <<std::endl;

// I need to add a checker for
// 1. (DONE)rows
// 2. (DONE)columns
// 3. (DONE)boxes
// 4. (DONE)All combined


//I need to figure out how to pass a 2D array
int array[9][9];
void rowsChecker(int sudokuVals[][9]){
    int rowCheck = 0;
    // i = rows
    // j = columns
    for(int row=0;row<9;row++){
        rowCheck = 0;
        for(int column=0;column<9;column++){
            rowCheck += sudokuVals[row][column];
        }
        if(rowCheck == 45){
            std::cout << "Row " << row + 1 << " passes the check\n" <<std::endl;
        } else {
            std::cout << "Row " << row + 1 << " FAILS\n" <<std::endl;
        }
    }
    std::cout << "End Rows Check \n" <<std::endl;
    std::cout << " \n" <<std::endl;

}

void columnsChecker(int sudokuVals[][9]){
    int columnCheck = 0;
    // i = rows
    // j = columns
    for(int column=0;column<9;column++){
        columnCheck = 0;
        for(int row=0;row<9;row++){
            columnCheck += sudokuVals[row][column];
        }
        if(columnCheck == 45){
            std::cout << "Column " << column + 1 << " passes the check\n" <<std::endl;
        } else {
            std::cout << "Column " << column + 1 << " FAILS\n" <<std::endl;
        }
    }
    std::cout << "End Columns Check \n" <<std::endl;
    std::cout << " \n" <<std::endl;
}

void boxesChecker(int sudokuVals[][9]){
    int boxCheck = 0;
    // i = rows
    // j = columns
    //I need an easy way to go through each box
    //I can do it manually
    /*int indexMap[9][9] = {{0,1,2,},
                          {4,5,6,7},
                          {8,9,10,11}
                         };*/
    int colBox[9] = {0,0,0,3,3,3,6,6,6};
    int rowBox[9] = {0,3,6,0,3,6,0,3,6};
    for(int box = 0;box<9;box++){
        boxCheck = 0;
    for(int column=0;column<3;column++){
        for(int row=0;row<3;row++){
           boxCheck += sudokuVals[row + rowBox[box]][column + colBox[box]];
        }
    }
    if(boxCheck == 45){
        std::cout << "Box " << box + 1 << " passes the check" <<std::endl;
    } else {
        std::cout << "Box " << box + 1 << " FAILS" <<std::endl;
    }
    }
    std::cout << "End Boxes Check \n" <<std::endl;
    std::cout << " \n" <<std::endl;

}

//Checker

void checkSudoku(int sudokuVals[][9]){
    rowsChecker(sudokuVals);
    columnsChecker(sudokuVals);
    boxesChecker(sudokuVals);
    std::cout << "End Sudoku Check \n" <<std::endl;
    std::cout << " \n" <<std::endl;
    //should I have some sort of if all pass Sudoku is good?
    //need return values for my 3 functions?
}
