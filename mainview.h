#ifndef MAINVIEW_H
#define MAINVIEW_H
#include <QGraphicsView>
#include <QPoint>
#include <QTime>

class QGraphicsScene;
class QGraphicsSceneMouseEvent;
class QMouseEvent;

class MainView : public QGraphicsView
{
public:
    MainView(QGraphicsScene *scene, QWidget *parent = Q_NULLPTR);


private:

    void mousePressEvent(QMouseEvent * e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void focusOutEvent ( QFocusEvent * event );
    void wheelEvent(QWheelEvent *event);
    bool event(QEvent * event);

    bool m_scrolling;
    bool m_selected;

    QPoint m_mousePressViewPoint;
    QPoint m_clickStartPoint;
    QTime time;
};

#endif // MAINVIEW_H
