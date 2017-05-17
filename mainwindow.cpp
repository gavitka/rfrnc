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
#include <QCoreApplication>
#include <QColor>

#include "NcFramelessHelper.h"
#include "mainview.h"
#include "mainscene.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //this->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowSystemMenuHint | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    //this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);

    mFh = new NcFramelessHelper;
    mFh->activateOn( this );
    mFh->useRubberBandOnMove(true);
    mFh->useRubberBandOnResize(true);

    openFile();
}

MainWindow::~MainWindow()
{
    delete m_mainview;
}

void MainWindow::openFile()
{
    QFile file (QString(":/Images/collage.psd"));
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

    MainScene* scene = new MainScene();
    scene->addWidget(label);

    m_mainview = new MainView(scene, this);
    //m_mainview->setDragMode(QGraphicsView::ScrollHandDrag);
    m_mainview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_mainview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QColor color;
    color.setNamedColor("#858e8e");
    m_mainview->setBackgroundBrush(QBrush(color, Qt::SolidPattern));

    setCentralWidget(m_mainview);

    setMinimumWidth(200);
    setMinimumHeight(200);

    QRect rect = QDesktopWidget().availableGeometry(this);

    move(rect.width()-500,
         rect.height()-500);

    resize(QSize(min(pix.size().width(),500),
                 min(pix.size().height(),500)));
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
//    m_nMouseClick_X_Coordinate = event->x();
//    m_nMouseClick_Y_Coordinate = event->y();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
//    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}

void MainWindow::focusOutEvent (QFocusEvent *event)
{
    //QFocusEvent event();
    QCoreApplication::sendEvent(m_mainview,event);
}


