#include "sudokugame.h"
#include "sudokubox.h"
#include "solver.h"
#include <QtWidgets>
#include <iostream>
#define LOG(x) std::cout << x <<std::endl;
///////////////////////NOTES////////////////////////////////////
/// \brief Sudoku::Sudoku
/// Feasture Metrics
/// 1. Have an auto fill for a suduku puzzle
///     -(done)Predefined puzzles
///         - button (spin box) that fills it (puzzle 1, 2 , 3, 4 , ... N)
///     -Random Puzzles
///         - (button) auto generates a random puzzle
///
/// 2. Solvers
///     - (button) that solves the puzzle for you and displays the answer (sub window)
///     - (done)(button) checks if the puzzle is solved
///
/// 3. (done)Create custom sudoku box object (Starting with this one)
///     - Use QPainter or whatever is most useful to create a custom sudoku box object
///
/// 4. (Optional) Features of our Sudoku Box Objects
///         - Drop down select options when clicked
///         - highlights when hovered over
///             -type to when hovered over
///             -CTRL to add guess
///
/// So, really my last 2 things to finish this project are:
///     1. create a suduko puzzle generator
///     2. create a pop-out of the stored solution
///
///
///
///
///
///
/////////////////////////////////////////////////////////////////////////
SudokuGame::SudokuGame(QWidget *parent)
    : QMainWindow(parent)
{
    SudokuGame::puzzlesBar();
    SudokuGame::sudokuBoard();
}

SudokuGame::~SudokuGame()
{
}

void SudokuGame::sudokuBoard()
{
    //Here we will build the actual Sudoku puzzle
    //Creates a Group widget
    QGroupBox *sodukuGroup = new QGroupBox(tr("Soduku"));
    //Generates a layout for the widget
    QGridLayout *sodukuLayout = new QGridLayout;
    //Creates 81 spin boxes as the sudoku entries
    //In the for loop we can assign and connect each spin box
    //ToDo: Use QPainter to draw the gridlines for the sudukuGroup box widget


    int RC[9] = {1,2,3,5,6,7,9,10,11};

    for (int i=0;i<9;i++ ) {
        for (int j=0;j<9;j++ ) {

            //SudokuBoxs[i][j] = new QSpinBox;
            SudokuBoxs[i][j] = new SudokuBox;
            //SudokuBoxs[i][j]->setRange(1,9);
            //SudokuBoxs[i][j]->setMaximumWidth(30);
            sodukuLayout->addWidget(SudokuBoxs[i][j], RC[i], RC[j], Qt::AlignCenter);

            connect(SudokuBoxs[i][j], &SudokuBox::isChanged, this, &SudokuGame::PrintCurrentVal);

            //connect(SudokuBoxs[i][j], QOverload<int>::of(&SudokuBox::valueChanged),
            //        this, &SudokuGame::PrintCurrentVal);

        }
    }

    //puzzles();
    PrintCurrentVal();

    QFrame *linea1H1 = new QFrame(this); // <<< this does the trick
    linea1H1->setLineWidth(2);
    linea1H1->setMidLineWidth(1);
    linea1H1->setFrameShape(QFrame::HLine);
    linea1H1->setFrameShadow(QFrame::Raised);
    sodukuLayout->addWidget(linea1H1, 4, 1, 1, 11);

    QFrame *linea1H2 = new QFrame(this); // <<< this does the trick
    linea1H2->setLineWidth(2);
    linea1H2->setMidLineWidth(1);
    linea1H2->setFrameShape(QFrame::HLine);
    linea1H2->setFrameShadow(QFrame::Raised);
    sodukuLayout->addWidget(linea1H2, 8, 1, 1, 11);

    QFrame *linea1V1 = new QFrame(this); // <<< this does the trick
    linea1V1->setLineWidth(2);
    linea1V1->setMidLineWidth(1);
    linea1V1->setFrameShape(QFrame::VLine);
    linea1V1->setFrameShadow(QFrame::Raised);
    sodukuLayout->addWidget(linea1V1, 0, 4, 12, 1);

    QFrame *linea1V2 = new QFrame(this); // <<< this does the trick
    linea1V2->setLineWidth(2);
    linea1V2->setMidLineWidth(1);
    linea1V2->setFrameShape(QFrame::VLine);
    linea1V2->setFrameShadow(QFrame::Raised);
    sodukuLayout->addWidget(linea1V2, 0, 8, 12, 1);


    //sodukuLayout->setRowStretch(0, 9);
    //sodukuLayout->addWidget(customPlot,  0, 1, 1, 4);
    sodukuGroup->setLayout(sodukuLayout);

       //SudokuBox *Box = new SudokuBox;

       QMainWindow::setCentralWidget(sodukuGroup);
}

void SudokuGame::puzzlesBar()
{

    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QToolBar *fileToolBar = addToolBar(tr("File"));
    const QIcon newIcon = QIcon::fromTheme("document-new", QIcon(":/images/new.png"));
    QAction *newAct = new QAction(newIcon, tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, &QAction::triggered, this, &SudokuGame::checkSolved);
    fileMenu->addAction(newAct);
    fileToolBar->addAction(newAct);


    const QIcon openIcon = QIcon::fromTheme("document-open", QIcon(":/images/open.png"));
    QAction *openAct = new QAction(openIcon, tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, &QAction::triggered, this, &SudokuGame::puzzles);
    fileMenu->addAction(openAct);
    fileToolBar->addAction(openAct);


    const QIcon saveIcon = QIcon::fromTheme("document-save", QIcon(":/images/save.png"));
    QAction *saveAct = new QAction(saveIcon, tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, &QAction::triggered, this, &SudokuGame::PrintCurrentVal);
    fileMenu->addAction(saveAct);
    fileToolBar->addAction(saveAct);


    fileMenu->addSeparator();

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    QAction *aboutAct = helpMenu->addAction(tr("&About"), this, &SudokuGame::about);
    aboutAct->setStatusTip(tr("Show the application's About box"));


    QAction *aboutQtAct = helpMenu->addAction(tr("About &Qt"), qApp, &QApplication::aboutQt);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));

}

void SudokuGame::about()
{
   QMessageBox::about(this, tr("About Application"),
            tr("The <b>Application</b> example demonstrates how to "
               "write modern GUI applications using Qt, with a menu bar, "
               "toolbars, and a status bar."));
}
//in sudokugame.cpp
void SudokuGame::puzzles(){
    int puzzle1[9][9] = {{5,3,0,0,7,0,0,0,0},
                         {6,0,0,1,9,5,0,0,0},
                         {0,9,8,0,0,0,0,6,0},
                         {8,0,0,0,6,0,0,0,3},
                         {4,0,0,8,0,3,0,0,1},
                         {7,0,0,0,2,0,0,0,6},
                         {0,6,0,0,0,0,2,8,0},
                         {0,0,0,4,1,9,0,0,5},
                         {0,0,0,0,8,0,0,7,9}
                        };
    for (int i = 0;i<9 ;i++) {
        for (int j = 0;j<9; j++) {
            SudokuBoxs[i][j]->val = puzzle1[i][j];
            //needs update function to redraw the whole puzzle
            update();
            /*
            //Makes it so the user can't change the puzzle
            if(puzzle1[i][j] != 0){
            SudokuBoxs[i][j]->boxEditable = false;
            }*/
        }

    }

}

void SudokuGame::checkSolved(){
    int sudokuVals[9][9];

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++){
            //sudokuVals[i][j] = SudokuBoxs[i][j]->getValue();
            sudokuVals[i][j] = SudokuBoxs[i][j]->val;
        }
    }

    checkSudoku(sudokuVals);

}

void SudokuGame::PrintCurrentVal()
{
    //int* sudokuVals[9] = new int[9][9];

    // Declare memory block of size M
    /*    int** sudokuVals = new int*[9];

        for (int i = 0; i < 9; i++) {

            // Declare a memory block
            // of size n
            sudokuVals[i] = new int[9];
        }*/

    int sudokuVals[9][9];

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++){
            //sudokuVals[i][j] = SudokuBoxs[i][j]->getValue();
            sudokuVals[i][j] = SudokuBoxs[i][j]->val;
        }
    }


    //std::cout << __func__ << std::endl;
    std::cout << "\n" <<std::endl;
    for (int i = 0; i < 9; i++)
    {
        std::cout << i << ": ";
        for (int j = 0; j < 9; j++){
            std::cout << sudokuVals[i][j] << '\t';}
        std::cout << std::endl;
    }

}


void SudokuGame::puzzleGenorator(){
    ////////////Tasks/////////////
    /// \brief puzzle Genorator
    /// The goal of this is to generate a sudoku puzzle
    ///
    /// 1. Gnerate the puzzle
    ///     a. Use a random number generator to generate the first element {1,2,3,4,5,6,7,8,9}
    ///     b. generate the second number in the row by getting a random number that hasn't been used
    ///        yet in the list
    ///     c. (milestone) generate the full first row.
    ///         -This is a big acomplishiment as it's what we need to finish the puzzle
    ///     d. Using the generate element - what is used method we can start generating the second row.
    ///         - generate element - value in box and row and column
    ///     e. run checker to see if it is a valid puzzle
    /// 2. Store the solution
    ///     a. store the puzzle into an array. This will be for later use
    ///     b. remove 6 elements at random from each row
    ///     c. populate puzzle
    /////////////////////////////

    //My code goes here
}


