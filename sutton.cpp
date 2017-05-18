#include "sutton.h"
#include <QPainter>
#include <QRectF>

Sutton::Sutton(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(100,100);
}

void Sutton::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    QPen pen(Qt::SolidLine);
    pen.setColor(QColor(255, 0, 0, 127));
    QRectF rect(rect().x(),rect().y(),rect().width(),rect().height());
    painter.setPen(pen);
    painter.drawEllipse(rect);
}
