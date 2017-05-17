#ifndef MAINSCENE_H
#define MAINSCENE_H
#include <QGraphicsScene>

class QEvent;
class QWidget;

class MainScene : public QGraphicsScene
{
public:
    MainScene();

    bool event(QEvent* event);
};

#endif // MAINSCENE_H
