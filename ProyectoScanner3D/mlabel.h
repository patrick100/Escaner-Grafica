#ifndef MLABEL_H
#define MLABEL_H
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>


class MLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MLabel(QWidget *parent = 0);

    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void leaveEvent(QEvent *);

    int x,y;

signals:
    void Mouse_Pressed();
    void Mouse_Pos();
    void Mouse_Left();

};

#endif // MLABEL_H
