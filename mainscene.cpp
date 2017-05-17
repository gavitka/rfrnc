#include "mainscene.h"
#include <QMainWindow>
#include <QEvent>

MainScene::MainScene()
    : QGraphicsScene()
{

}

bool MainScene::event(QEvent *event)
{
    return false;
}
