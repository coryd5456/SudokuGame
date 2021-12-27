#include "sudokugame.h"
#include "solver.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SudokuGame w;
    w.show();
    return a.exec();
}
