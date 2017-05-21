#include "mainview.h"
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QFocusEvent>
#include <QCoreApplication>
#include <Qt>
#include <QScrollBar>
#include <QDebug>
#include <math.h>
#include <QSettings>

using namespace std;

MainView::MainView(QGraphicsScene *scene, QWidget *parent, QSettings *settingsValue):
    QGraphicsView(scene, parent),
    settings(settingsValue),
    m_scaleFactor (0),
    m_scale(0)
{
    m_scrolling = false;
    m_selected = false;
    setScale(settings->value("sceneScale").toInt());
    rememberScroll();
    setStyleSheet("border: 2px solid #0f3c38");
}

void MainView::rememberScroll() // slot?
{
    QScrollBar *hBar = horizontalScrollBar();
    QScrollBar *vBar = verticalScrollBar();
    qDebug() << "remx" << settings->value("sceneX").toInt();
    qDebug() << "remy" << settings->value("sceneY").toInt();
    hBar->setValue(settings->value("sceneX").toInt());
    vBar->setValue(settings->value("sceneY").toInt());
    qDebug() << "wasx" << hBar->value();
    qDebug() << "wasy" << vBar->value();
}

void MainView::saveScroll() // slot?
{
    QScrollBar *hBar = horizontalScrollBar();
    QScrollBar *vBar = verticalScrollBar();
    qDebug() << "savx" << hBar->value();
    qDebug() << "savy" << vBar->value();
    settings->setValue("sceneX",hBar->value());
    settings->setValue("sceneY",vBar->value());
}

void MainView::setScale(int value)
{
    const qreal minFactor = .1;
    const qreal maxFactor = 10.0;

    value = value > log(maxFactor)*4 ? log(maxFactor)*4 : value;
    value = value < log(minFactor)*4 ? log(minFactor)*4 : value;

    m_scale = value;

    m_scaleFactor = exp((qreal)m_scale/4);
    m_scaleFactor = (value == -1 ||value == 1)? 1 : m_scaleFactor;

    setTransformationAnchor(QGraphicsView::AnchorViewCenter);
    setTransform(QTransform(m_scaleFactor, 0, 0, m_scaleFactor, 0, 0));

    settings->setValue("sceneScale", m_scale);
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

        qDebug() << "wasx" << hBar->value();
        qDebug() << "wasy" << vBar->value();

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

    if (steps > 0) {
        setScale(scale() + 1);
    }
    else if (steps < 0) {
        setScale(scale() - 1);
    }
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
