#ifndef SUDOKUGAME_H
#define SUDOKUGAME_H

#include <QMainWindow>
#include <QtWidgets>
#include "solver.h"
#include "sudokubox.h"


class SudokuBox;

class SudokuGame : public QMainWindow
//class SudokuGame : public QWidget
{
    Q_OBJECT


public:
    SudokuGame(QWidget *parent = nullptr);
    ~SudokuGame();
    void sudokuBoard();
    void puzzles();
    void puzzlesBar();
    void about();
    void checkSolved();
    void puzzleGenorator();
    //void PrintCurrentVal();

//Private Variables

public slots:
    void PrintCurrentVal();
private:
    SudokuBox *SudokuBoxs[9][9];
    int *genSudokuPuzzle[9][9];
    int *genPuzzleSolution[9][9];
    //QSpinBox *SudokuBoxs[9][9];


};
#endif // SUDOKUGAME_H
