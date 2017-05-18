#include "sutton.h"
#include <QPainter>
#include <QRectF>

Sutton::Sutton(QWidget *parent) : QWidget(parent), m_mainclr(QColor(0, 0, 255, 255))
{
    setMinimumSize(30,30);
}

void Sutton::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    QPen pen(Qt::NoPen);

    QBrush brush(m_mainclr);
    QRectF rect(rect().x(),
                rect().y(),
                rect().width()-1,
                rect().height()-1);

    painter.setBrush(brush);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawEllipse(rect);
}
