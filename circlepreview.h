#ifndef CIRCLEPREVIEW_H
#define CIRCLEPREVIEW_H

#include <QWidget>
#include <QTime>

#include "NcFramelessHelper.h"

class QPixmap;

class CirclePreview : public QWidget
{
    Q_OBJECT
public:
    explicit CirclePreview(QWidget *parent = 0);

signals:
    void showMainWindow(int, int);

public slots:
    void setPixmap(QPixmap* pixmap, int cx, int cy);

private:
    void paintEvent(QPaintEvent *event);

    NcFramelessHelper* mFh;

    QPoint m_mousePressViewPoint;
    QPoint m_clickStartPoint;
    QPixmap *m_pixmap;
    QTime time;
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // CIRCLEPREVIEW_H
