#include "mainview.h"
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QCoreApplication>
#include <QCoreApplication>
#include <Qt>
#include <QScrollBar>

MainView::MainView(QGraphicsScene *scene, QWidget *parent):
    QGraphicsView(scene, parent)
{
    m_scrolling = false;
}

void MainView::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::RightButton) {
        m_scrolling = true;
        m_mousePressViewPoint = e->pos();
        viewport()->setCursor(Qt::ClosedHandCursor);
    }
    else {
        QMouseEvent event(e->type(), e->localPos(), e->button(), e->buttons(), e->modifiers());
        QCoreApplication::sendEvent(parent(),&event);
    }
}


void MainView::mouseMoveEvent(QMouseEvent *e)
{
    if(m_scrolling) {
        QScrollBar *hBar = horizontalScrollBar();
        QScrollBar *vBar = verticalScrollBar();
        QPoint delta = (e->pos() - m_mousePressViewPoint);
        hBar->setValue(hBar->value() + (isRightToLeft() ? delta.x() : -delta.x()));
        vBar->setValue(vBar->value() - delta.y());
        m_mousePressViewPoint = e->pos();
        //m_scrolling = false;
    }
    else {
        QMouseEvent event(e->type(), e->localPos(), e->button(), e->buttons(), e->modifiers());
        QCoreApplication::sendEvent(parent(),&event);
    }
}


void MainView::mouseReleaseEvent(QMouseEvent *e)
{
    m_scrolling = false;
    viewport()->setCursor(Qt::OpenHandCursor);
    if(e->button() == Qt::RightButton) {

    }
    else {
        QMouseEvent event(e->type(), e->localPos(), e->button(), e->buttons(), e->modifiers());
        QCoreApplication::sendEvent(parent(),&event);
    }
}
