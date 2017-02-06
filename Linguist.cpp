#include "Linguist.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QIcon>
#include <QPalette>
#include <QPixmap>
#include <QBrush>
#include <QMouseEvent>
#include <QToolTip>
#include <QTextStream>
#include <QDebug>
#include <QPainter>
#include <QBitmap>
#include <QRect>
#include <QApplication>
#include <QDesktopWidget>

bool isDrawing = false;
QCursor cursorPic;
QSize foneSize;

Linguist::Linguist(QWidget *parent)
    : QWidget(parent)
{

    setWindowTitle(tr("Spyder"));
    setWindowIcon(QIcon(":/img/Images/icon2.ico"));

    setWindowState(Qt::WindowActive);

    setWindowFlags(Qt::Window);

    QPixmap fone = QPixmap(":/img/Images/img002.jpg");
    QBrush brush = QBrush(fone);

    cursorPic = QCursor((Qt::ArrowCursor)) ;

    QPalette myPalette;
    myPalette.setBrush(QPalette::Inactive,QPalette::Window,brush);
    setPalette(myPalette);

    foneSize = fone.size();
    resize(foneSize);

    setMaximumSize(foneSize);
    setMinimumSize(foneSize);
    setFixedSize(foneSize);


}

Linguist::~Linguist()
{

}

void Linguist::mousePressEvent ( QMouseEvent * event )
{
    int cursoreX;
    int cursoreY;
    QString str;
    QTextStream tstream(&str);
    //Only on M2 key
    auto mouseBottom = ( event ->buttons() );
    switch (mouseBottom)
    {
    case (Qt::RightButton):
        //extracting coordinates of the cursor
        cursoreX = (event ->x() );
        cursoreY = (event ->y() );


        str = "x=" + (QString().setNum(cursoreX) )
            + "y=" + (QString().setNum(cursoreY) );
        //on CTRL
        if(event ->modifiers() & Qt::ControlModifier )
        {
            QToolTip::showText(event ->globalPos(),str);
        }
        break;
        //draw on M1 key
    case (Qt::LeftButton):
        isDrawing = !isDrawing;
        setMouseTracking(true);
        break;
    default:
        //
        break;
    }
}

void Linguist::mouseReleaseEvent(QMouseEvent * event )
{
    //if mouse press off, draw stop
    isDrawing = false;
    Linguist::unsetCursor();
    setMouseTracking(false);
}

void Linguist::mouseMoveEvent(QMouseEvent * event)
{
    //limit cursor area
           if (event->y() < 0){
               //cursor over up
               QCursor::setPos(event->globalX() ,Linguist::geometry().y());
           }
           if(event->y()> Linguist::geometry().height()){
               //cursor over down
               QCursor::setPos(mapToGlobal(QPoint(event->x() ,Linguist::geometry().height()) ));
           }
           if(event->x() < 0 ){
           //cursor over left
               QCursor::setPos(Linguist::geometry().x(), event->globalY());
           }
           if(event->x() > Linguist::geometry().width()){
           //cursor over right
               QCursor::setPos(mapToGlobal(QPoint(Linguist::geometry().width(), event->y())));
           }
    Linguist::repaint();
}

void Linguist::paintEvent(QPaintEvent * event)
{
    QPainter web(this);
    web.setPen(QPen(Qt::black, 2 , Qt::SolidLine) );
    auto cursor = mapFromGlobal(QCursor::pos());
    cursorPic = QCursor(QPixmap(":/img/Images/icon1.ico"), -1, -1) ;
    QRect rect = Linguist::rect();
    //drow on M1 key
    if (isDrawing == true)
    {
        this->setCursor(cursorPic);
        web.drawLine(cursor.x(), cursor.y(), 0, 0);
        web.drawLine(cursor.x(), cursor.y(), 0, rect.height());
        web.drawLine(cursor.x(), cursor.y(), rect.width(), 0);
        web.drawLine(cursor.x(), cursor.y(), rect.width(), rect.height());

        web.drawLine(cursor.x(), cursor.y(), rect.width()/2, 0);
        web.drawLine(cursor.x(), cursor.y(), rect.width()/2, rect.height());
        web.drawLine(cursor.x(), cursor.y(), 0, rect.height()/2);
        web.drawLine(cursor.x(), cursor.y(), rect.width(), rect.height()/2);
    }

}

void Linguist::resizeEvent(QResizeEvent * event)
{   //resize window
    QDesktopWidget desktop;
    QRect rect = desktop.availableGeometry(desktop.primaryScreen());    //size of screen
    QPoint screenCenter = rect.center();
    screenCenter.setX(screenCenter.x() - (this->width()));
    screenCenter.setY(screenCenter.y() - (this->height()));
    move(screenCenter);

}
