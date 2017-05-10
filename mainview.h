#ifndef MAINVIEW_H
#define MAINVIEW_H
#include <QGraphicsView>
#include <QPoint>

class QGraphicsScene;
class QGraphicsSceneMouseEvent;
class QMouseEvent;

class MainView : public QGraphicsView
{
public:
    MainView(QGraphicsScene *scene, QWidget *parent = Q_NULLPTR);

    void mousePressEvent(QMouseEvent * e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private:

    bool m_scrolling;
    QPoint m_mousePressViewPoint;

};

#endif // MAINVIEW_H
