#include "mainview.h"
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QFocusEvent>
#include <QCoreApplication>
#include <QCoreApplication>
#include <Qt>
#include <QScrollBar>
#include <QDebug>

MainView::MainView(QGraphicsScene *scene, QWidget *parent):
    QGraphicsView(scene, parent)
{
    m_scrolling = false;
    m_selected = false;
}

void MainView::mousePressEvent(QMouseEvent *e)
{
    time.start();
    m_mousePressViewPoint = e->pos();
    if (m_selected) {
        m_scrolling = true;
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
    QPoint delta = (e->pos() - m_mousePressViewPoint);
    int deltasize = std::abs(delta.x()) + std::abs(delta.y());

    if (difference < 200 && deltasize < 10) {
        if (m_selected == true) {
            m_selected = false;
            setStyleSheet("border: none");
        }
        else {
            setStyleSheet("border: 3px solid orange");
            m_selected = true;
        }
    }

    if (m_scrolling) {
        m_scrolling = false;
        viewport()->setCursor(Qt::OpenHandCursor);
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
    setStyleSheet("border: none");
}


