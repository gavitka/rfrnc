#include "circlepreview.h"
#include <QPainter>
#include <QMouseEvent>
#include <QBrush>
#include <QPen>
#include <QDebug>
#include <QColor>

const int circlesize = 100;

using namespace std;

CirclePreview::CirclePreview(QWidget *parent) : QWidget(parent)
{
    mFh = new NcFramelessHelper;
    mFh->activateOn( this );
    mFh->useRubberBandOnMove(false);
    mFh->useRubberBandOnResize(true);
    mFh->setWidgetResizable(false);

    resize(QSize(circlesize, circlesize));

    setAttribute(Qt::WA_TranslucentBackground);
}

void CirclePreview::setPixmap(QPixmap *pixmap, int cx, int cy)
{
    m_pixmap = pixmap;
    this->move(cx - circlesize/2,
               cy - circlesize/2);
    this->show();
}

void CirclePreview::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);

    QPen pen(QColor("black"));

    QBrush brush = QBrush(*m_pixmap);

    int maxsize = max(m_pixmap->width(), m_pixmap->height());
    qreal fact = (qreal)circlesize / maxsize;

    brush.setTransform(QTransform(fact*2,0,0,fact*2,0,-circlesize/2));

    painter.setPen(pen);
    painter.setBrush(brush);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawEllipse(rect());
}

void CirclePreview::mousePressEvent(QMouseEvent *event){
    time.start();
    m_clickStartPoint = event->globalPos();
    m_mousePressViewPoint = event->pos();
}

void CirclePreview::mouseReleaseEvent(QMouseEvent * event)
{
    int difference = time.elapsed();
    QPoint delta = (event->globalPos() - m_clickStartPoint);
    int deltasize = std::abs(delta.x()) + std::abs(delta.y());
    if (difference < 200 && deltasize < 10) {
        this->hide();
        showMainWindow(this->frameGeometry().x() + this->frameGeometry().width()/2,
                       this->frameGeometry().y() + this->frameGeometry().height()/2); // passes center point
    }
}
