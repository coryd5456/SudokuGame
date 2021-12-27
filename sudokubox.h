#ifndef SUDOKUBOX_H
#define SUDOKUBOX_H
#include <QMainWindow>
#include <QShortcut>
#include <QWidget>
class QKeyEvent;
//class SudokuBox : public QMainWindow
class SudokuBox : public QWidget
{
    //Needs to be a Q_Object?
    Q_OBJECT
    //Public Variables
public:
    int val = 0;
    bool boxEditable = true;
    //Private Variables
private:
    QShortcut *sudokuEntry[9];

    bool click = false;
    bool valSelect = false;
public:
    SudokuBox(QWidget *parent = nullptr);
    //SudokuBox(QMainWindow *parent = nullptr);
    int getValue(){
        return val;
    }
    void setValue(int v){
        val = v;
    }


    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
    //void eventAll(QEvent *event);

signals:
    void isChanged();
private slots:
    /*void keyPressed1();
    void keyPressed2();
    void keyPressed3();
    void keyPressed4();
    void keyPressed5();
    void keyPressed6();
    void keyPressed7();
    void keyPressed8();
    void keyPressed9();*/

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    //void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *eventKey) override;
    void keyReleaseEvent(QKeyEvent *) override;

};

#endif // SUDOKUBOX_H


