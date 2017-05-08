#include "mainwindow.h"
#include <qpsdhandler.h>
#include <QImage>
#include <QFile>
#include <QLabel>
#include <QPixmap>
#include <QString>
#include <QDebug>
#include <QGraphicsView>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowSystemMenuHint | Qt::WindowStaysOnTopHint );
    // | Qt::FramelessWindowHint

    QFile file (QString("E:/Developement/untitled1/collage.psd"));
    file.open(QIODevice::ReadOnly);
    auto handler = new QPsdHandler();
    QImage image;
    handler->setDevice(&file);
    handler->setFormat("psd");
    handler->read(&image);

    QLabel* label = new QLabel();
    QPixmap pix = QPixmap::fromImage(image);
    label->setPixmap(pix);
    label->resize(pix.size());

    QGraphicsScene* scene = new QGraphicsScene();
    scene->addWidget(label);

    QGraphicsView* view = new QGraphicsView(scene, parent);
    view->setDragMode(QGraphicsView::ScrollHandDrag);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setCentralWidget(view);
}

MainWindow::~MainWindow()
{

}
