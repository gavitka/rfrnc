#include "mainscene.h"
#include <QMainWindow>
#include <QEvent>

MainScene::MainScene()
    : QGraphicsScene()
{

}

bool MainScene::event(QEvent *event)
{
    Q_UNUSED(event);
    return false;
}
