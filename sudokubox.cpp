#include "sudokubox.h"
#include <QPainter>
#include <QMainWindow>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QShortcut>
#include <stdlib.h>
#include <iostream>
#include <string>
#define LOG(x) std::cout << x <<std::endl

//////////////NOTES/////////////////////
/// \brief SudokuBox::SudokuBox
/// \param parent
/// 1. (DONE)This needs to do 2 things
///     -accept numbers when the user is typing them in
///     -default to a number that we give it for a puzzle
///
///
/// 2. (DONE) Need to resolve why these aren't appearing in my layout
///     -I suspect that it's because nothing is in the QWidget part
///     -(ANSWER)
///
/// 3. (DONE) Need to spend some real time learning QPainter to really learn how
///     to make my own stuff

SudokuBox::SudokuBox(QWidget *parent): QWidget(parent)
//SudokuBox::SudokuBox(QMainWindow *parent): QMainWindow(parent)
{
    /*for (int i =0; i<9 ; i++ ) {
        sudokuEntry[i] = new QShortcut(this);
        sudokuEntry[i]->setKey(49+i);
        //connect(&i, SIGNAL(activated()), &i , SLOT(digitClicked2(int)));
        //connect(keyF[i], SIGNAL(activated()), this , SLOT(digitClicked2(int)));
        //this->i;
    }
    connect(sudokuEntry[0], SIGNAL(activated()), this , SLOT(keyPressed1()));
    connect(sudokuEntry[1], SIGNAL(activated()), this , SLOT(keyPressed2()));
    connect(sudokuEntry[2], SIGNAL(activated()), this , SLOT(keyPressed3()));
    connect(sudokuEntry[3], SIGNAL(activated()), this , SLOT(keyPressed4()));
    connect(sudokuEntry[4], SIGNAL(activated()), this , SLOT(keyPressed5()));
    connect(sudokuEntry[5], SIGNAL(activated()), this , SLOT(keyPressed6()));
    connect(sudokuEntry[6], SIGNAL(activated()), this , SLOT(keyPressed7()));
    connect(sudokuEntry[7], SIGNAL(activated()), this , SLOT(keyPressed8()));
    connect(sudokuEntry[8], SIGNAL(activated()), this , SLOT(keyPressed9()));
    */
    //setFocusPolicy(Qt::ClickFocus);
    setBackgroundRole(QPalette::Base);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}



QSize SudokuBox::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize SudokuBox::sizeHint() const
{
    return QSize(50, 50);
}
/*
void SudokuBox::eventAll(QEvent *event){
    LOG("something happened \n");
    if(event->type()==QEvent::KeyPress){
        QKeyEvent *press = static_cast<QKeyEvent *>(event);
        LOG(press);
    }else if(event->type() == QEvent::MouseButtonPress){
        QMouseEvent *press = static_cast<QMouseEvent *>(event);
        LOG(press);
        LOG("AAAAAAAAAAAAAAAAAAAHHHHHHH\n");
    }
}*/

void SudokuBox::mousePressEvent(QMouseEvent *event)
//! [11] //! [12]
{
    if (event->button() == Qt::LeftButton) {
        //connect();
        //val = 6;
        //setFocusPolicy(Qt::ClickFocus);
        click = true;
        update();
        LOG("Click Pressed");
    }
}
/*
void SudokuBox::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && scribbling)
        drawLineTo(event->position().toPoint());
}*/

void SudokuBox::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        setFocus();
        click = false;
        //val = 7;
        //update();
        //click = false;
        valSelect = false;
        //LOG(click);
        LOG("Click Release");
    }
}
/*
void SudokuBox::keyPressed1(){
    val = 1;
    valSelect = true;
    update();
    LOG(val);
}

void SudokuBox::keyPressed2(){
    val = 2;
    valSelect = true;
    update();
    LOG(val);
}

void SudokuBox::keyPressed3(){
    val = 3;
    valSelect = true;
    update();
    LOG(val);
}

void SudokuBox::keyPressed4(){
    val = 4;
    valSelect = true;
    update();
    LOG(val);
}

void SudokuBox::keyPressed5(){
    val = 5;
    valSelect = true;
    update();
    LOG(val);
}

void SudokuBox::keyPressed6(){
    val = 6;
    valSelect = true;
    update();
    LOG(val);
}

void SudokuBox::keyPressed7(){
    val = 7;
    valSelect = true;
    update();
    LOG(val);
}

void SudokuBox::keyPressed8(){
    val = 8;
    valSelect = true;
    update();
    LOG(val);
}

void SudokuBox::keyPressed9(){
    val = 9;
    valSelect = true;
    update();
    LOG(val);
}*/

void SudokuBox::keyPressEvent(QKeyEvent *eventKey) {
    if(eventKey->isAccepted() == true){
    //LOG("A Key was pressed");
    qDebug("keyPress %d", eventKey->key());
    valSelect = true;

    switch (eventKey->key()) {
    case Qt::Key_1:
        val = 1;
        //LOG("A Key was pressed");
        break;
    case Qt::Key_2:
        val = 2;
        break;
    case Qt::Key_3:
        val = 3;
        break;
    case Qt::Key_4:
        val = 4;
        break;
    case Qt::Key_5:
        val = 5;
        break;
    case Qt::Key_6:
        val = 6;
        break;
    case Qt::Key_7:
        val = 7;
        break;
    case Qt::Key_8:
        val = 8;
        break;
    case Qt::Key_9:
        val = 9;
        break;
    }
    emit isChanged();
    update();
    LOG(val);
    }
}

void SudokuBox::keyReleaseEvent(QKeyEvent *event){
    if(event->isAccepted() == true){
    LOG("Yay,we released the stuff");
    }
}

void SudokuBox::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.translate(width() / 2, height() / 2);

    int diameter = 50;

    QRect rect = QRect(-diameter / 2, -diameter / 2, diameter, diameter);

    painter.drawRect(rect);

    if (boxEditable){
        switch (val) {
        case 0:
            painter.drawText(rect, Qt::AlignCenter, tr("Fill"));
            break;
        case 1:
            painter.drawText(rect, Qt::AlignCenter, tr("1"));
            break;
        case 2:
            painter.drawText(rect, Qt::AlignCenter, tr("2"));
            break;
        case 3:
            painter.drawText(rect, Qt::AlignCenter, tr("3"));
            break;
        case 4:
            painter.drawText(rect, Qt::AlignCenter, tr("4"));
            break;
        case 5:
            painter.drawText(rect, Qt::AlignCenter, tr("5"));
            break;
        case 6:
            painter.drawText(rect, Qt::AlignCenter, tr("6"));
            break;
        case 7:
            painter.drawText(rect, Qt::AlignCenter, tr("7"));
            break;
        case 8:
            painter.drawText(rect, Qt::AlignCenter, tr("8"));
            break;
        case 9:
            painter.drawText(rect, Qt::AlignCenter, tr("9"));
            break;
       }

    //}else{
    //painter.drawText(rect, Qt::AlignCenter, tr("Fill"));
    }


}
