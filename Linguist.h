#ifndef LAB1_H
#define LAB1_H

#include <QWidget>

class Linguist : public QWidget
{
    Q_OBJECT

public:
    explicit Linguist(QWidget *parent = 0);
    ~Linguist();

protected:
    virtual void mousePressEvent ( QMouseEvent * event );
    virtual void mouseReleaseEvent ( QMouseEvent * event );
    virtual void mouseMoveEvent(QMouseEvent * event);
    virtual void paintEvent(QPaintEvent * event);
    virtual void resizeEvent(QResizeEvent * event);
};

#endif // LAB1_H
