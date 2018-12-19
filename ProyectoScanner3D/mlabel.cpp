
#include "mlabel.h"

MLabel::MLabel(QWidget *parent):QLabel(parent)
{

}

void MLabel::mouseMoveEvent(QMouseEvent *ev)
{
    emit Mouse_Pos();
}

void MLabel::mousePressEvent(QMouseEvent *ev)
{
    this->x = ev->x();
    this->y = ev->y();
    emit Mouse_Pressed();
}

void MLabel::leaveEvent(QEvent *)
{
    emit Mouse_Left();
}




