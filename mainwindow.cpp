#include "mainwindow.h"
#include <qpsdhandler.h>
#include <QImage>
#include <QFile>
#include <QLabel>
#include <QPixmap>
#include <QString>
#include <QDebug>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QSize>
#include <QDesktopWidget>
#include <math.h>

#include "mainview.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowSystemMenuHint | Qt::WindowStaysOnTopHint );
    // | Qt::FramelessWindowHint

    QDesktopWidget dw;

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
    //label->resize(pix.size());

    QGraphicsScene* scene = new QGraphicsScene();
    scene->addWidget(label);

    MainView* view = new MainView(scene, this);
    view->setDragMode(QGraphicsView::ScrollHandDrag);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setCentralWidget(view);

    setMinimumWidth(200);
    setMinimumHeight(200);

    QRect rect = QDesktopWidget().availableGeometry(this);

    move(rect.width()-500,
         rect.height()-500);

    resize(QSize(min(pix.size().width(),500),
                 min(pix.size().height(),500)));
}

MainWindow::~MainWindow()
{

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}
