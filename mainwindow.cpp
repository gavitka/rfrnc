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
#include <QPushButton>
#include <QChar>
#include <QApplication>

#include <QTWidgets>

#include "NcFramelessHelper.h"
#include "mainview.h"
#include "mainscene.h"
#include "sutton.h"

using namespace std;

const int marginAmount = 10;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //this->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowSystemMenuHint | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    //this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);

    mFh = new NcFramelessHelper;
    mFh->activateOn( this );
    mFh->useRubberBandOnMove(true);
    mFh->useRubberBandOnResize(true);

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

    MainScene* scene = new MainScene();
    scene->addWidget(label);

    m_mainview = new MainView(scene, this);
    //m_mainview->setDragMode(QGraphicsView::ScrollHandDrag);
    m_mainview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_mainview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QColor color;
    color.setNamedColor("#858e8e");
    m_mainview->setBackgroundBrush(QBrush(color, Qt::SolidPattern));

    //----------------------------------------------------------------------------------------------------------
    // NOT WORKING

    Sutton * pushButton2 = new Sutton(this);
    pushButton2->setMainclr("#547a6b");
    pushButton2->setHoverclr("#39df9d");
    pushButton2->setSymbol(QChar(0xE972));


    Sutton * pushButton3 = new Sutton(this);
    pushButton3->setMainclr("#547a6b");
    pushButton3->setHoverclr("#39df9d");
    pushButton3->setSymbol(QChar(0xE712));

    Sutton * quitButton = new Sutton(this);
    quitButton->setMainclr("#547a6b");
    quitButton->setHoverclr("#9e3d3d");
    quitButton->setSymbol(QChar(0xE711));
    QObject::connect(quitButton, SIGNAL(clicked()), this, SLOT(quitApp()));

    //auto pushButton4 = new QPushButton(this);
    QSpacerItem *spaceritem1 = new QSpacerItem(marginAmount*1.5,
                                               marginAmount*1.5,
                                               QSizePolicy::Fixed,
                                               QSizePolicy::Fixed);
    QSpacerItem *spaceritem2 = new QSpacerItem(marginAmount*1.5,
                                               marginAmount*1.5,
                                               QSizePolicy::Fixed,
                                               QSizePolicy::Fixed);

    QHBoxLayout *hboxLayout = new QHBoxLayout();
//    hboxLayout->addSpacerItem(spaceritem1);
    hboxLayout->addWidget(pushButton3, 0, Qt::AlignRight | Qt::AlignBottom);
    hboxLayout->addSpacerItem(spaceritem1);
    hboxLayout->addWidget(pushButton2, 0, Qt::AlignRight | Qt::AlignBottom);
    hboxLayout->addSpacerItem(spaceritem2);
    hboxLayout->addWidget(quitButton, 0, Qt::AlignRight | Qt::AlignBottom);
    //hboxLayout->addWidget(pushButton4, 0, Qt::AlignRight | Qt::AlignBottom);
    hboxLayout->setSpacing(0);

    //    QStackedLayout *stackedLayout = new QStackedLayout();
    //    //stackedLayout->insertWidget(1, layer1);
    //    stackedLayout->insertWidget(0, m_mainview);
    //    stackedLayout->setStackingMode(QStackedLayout::StackAll);

    QHBoxLayout *hboxLayout1 = new QHBoxLayout();
    hboxLayout1->addWidget(m_mainview);
    hboxLayout1->setMargin(0);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(hboxLayout1);

    overlayWidget = new QWidget(centralWidget);
    overlayWidget->setLayout(hboxLayout);
    overlayWidget->setFixedSize(120,40);

    //----------------------------------------------------------------------------------------------------------

    //    pushButton = new QPushButton("shit", this);
    //    QLabel *label2 = new QLabel("Ssibal", this);
    //    QSpacerItem *spaceritem1 = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding);

    //    QHBoxLayout *hboxLayout = new QHBoxLayout();
    //    hboxLayout->addSpacerItem(spaceritem1);
    //    hboxLayout->addWidget(label2, 0, Qt::AlignRight | Qt::AlignBottom);
    //    hboxLayout->addWidget(pushButton, 0, Qt::AlignRight | Qt::AlignBottom);

    //    QWidget *layer1 = new QWidget(this);
    //    layer1->setLayout(hboxLayout);

    //    QStackedLayout *stackedLayout = new QStackedLayout();
    //    //stackedLayout->insertWidget(1, layer1);
    //    stackedLayout->insertWidget(0, m_mainview);
    //    stackedLayout->setStackingMode(QStackedLayout::StackAll);

    //    QWidget *centralWidget = new QWidget(this);
    //    centralWidget->setLayout(stackedLayout);

    //----------------------------------------------------------------------------------------------------------

    setCentralWidget(centralWidget);

    QWidget::setAttribute(Qt::WA_NativeWindow, true);

    setMinimumWidth(overlayWidget->width()+marginAmount*2); // TODO: FIX
    setMinimumHeight(overlayWidget->height()+marginAmount*2);

    QRect rect = QDesktopWidget().availableGeometry(this);

    move(rect.width()-500,
         rect.height()-500);

    resize(QSize(min(pix.size().width(),500),
                 min(pix.size().height(),500)));

    overlayWidget->move(width() - overlayWidget->width() - marginAmount, height() - overlayWidget->height() - marginAmount);
}

MainWindow::~MainWindow()
{
    delete m_mainview;
}

void MainWindow::focusOutEvent (QFocusEvent *event)
{
    //QFocusEvent event();
    QCoreApplication::sendEvent(m_mainview,event);
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    Q_UNUSED(event);
    overlayWidget->move(width() - overlayWidget->width() - marginAmount, height() - overlayWidget->height() - marginAmount);
}

void MainWindow::quitApp()
{
    QApplication::quit();
}


