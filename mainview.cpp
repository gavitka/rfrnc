#include "mainview.h"
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QFocusEvent>
#include <QCoreApplication>
#include <Qt>
#include <QScrollBar>
#include <QDebug>
#include <math.h>

using namespace std;

MainView::MainView(QGraphicsScene *scene, QWidget *parent):
    QGraphicsView(scene, parent)
{
    m_scrolling = false;
    m_selected = false;
    setStyleSheet("border: 2px solid #0f3c38");
}

void MainView::mousePressEvent(QMouseEvent *e)
{
    time.start();
    m_clickStartPoint = e->pos();
    if (m_selected) {
        m_scrolling = true;
        m_mousePressViewPoint = e->pos();
        viewport()->setCursor(Qt::ClosedHandCursor);
    }
    else {
        QMouseEvent event(e->type(), e->localPos(), e->button(), e->buttons(), e->modifiers());
        QCoreApplication::sendEvent(parent(),&event);
    }
}

void MainView::mouseReleaseEvent(QMouseEvent *e)
{
    int difference = time.elapsed();
    QPoint delta = (e->pos() - m_clickStartPoint);
    int deltasize = std::abs(delta.x()) + std::abs(delta.y());
    if (difference < 200 && deltasize < 10) {
        if (m_selected == true) {
            m_selected = false;
            setStyleSheet("border: 2px solid #0f3c38");
        }
        else {
            setStyleSheet("border: 3px solid orange");
            m_selected = true;
        }
    }

    if (m_scrolling) {
        m_scrolling = false;
        viewport()->setCursor(Qt::OpenHandCursor);
        viewport()->unsetCursor();
    }
    else {
        QMouseEvent event(e->type(), e->localPos(), e->button(), e->buttons(), e->modifiers());
        QCoreApplication::sendEvent(parent(),&event);
    }
}

void MainView::mouseMoveEvent(QMouseEvent *e)
{
    if(m_selected && m_scrolling) {
        QScrollBar *hBar = horizontalScrollBar();
        QScrollBar *vBar = verticalScrollBar();
        QPoint delta = (e->pos() - m_mousePressViewPoint);
        hBar->setValue(hBar->value() + (isRightToLeft() ? delta.x() : -delta.x()));
        vBar->setValue(vBar->value() - delta.y());
        m_mousePressViewPoint = e->pos();
    }
    else {
        QMouseEvent event(e->type(), e->localPos(), e->button(), e->buttons(), e->modifiers());
        QCoreApplication::sendEvent(parent(),&event);
    }
}

void MainView::focusOutEvent(QFocusEvent *event)
{
    Q_UNUSED(event);
    m_selected = false;
    setStyleSheet("border: 2px solid #0f3c38");
}

void MainView::wheelEvent(QWheelEvent* event)
{
    if (!m_selected) return;
    // Typical Calculations (Ref Qt Doc)
    const int degrees = event->delta() / 8;
    int steps = degrees / 15;

    static qreal scale = 0;
    static qreal scaleFactor = 0;
    const qreal minFactor = .1;
    const qreal maxFactor = 10.0;

    if (steps > 0 && scaleFactor < maxFactor) {
        scale ++;
    }
    else if (steps < 0 && scaleFactor > minFactor) {
        scale --;
    }

    scaleFactor = exp(scale/4);
    scaleFactor = (scaleFactor <= minFactor) ?
                minFactor :
                (scaleFactor >= maxFactor) ? maxFactor : scaleFactor;

    qDebug() << "scale" << scale;
    qDebug() << "scaleFactor" << scaleFactor;


    setTransformationAnchor(QGraphicsView::AnchorViewCenter);
    setTransform(QTransform(scaleFactor, 0, 0, scaleFactor, 0, 0));
}

bool MainView::event(QEvent *event)
{
    if (    event->type() == QEvent::MouseButtonDblClick ||
            event->type() == QEvent::MouseButtonPress ||
            event->type() == QEvent::MouseButtonRelease ||
            event->type() == QEvent::MouseMove   ) {
        return false;
    } else {
        QGraphicsView::event(event);
        return true;
    }
}
