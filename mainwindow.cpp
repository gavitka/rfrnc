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

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    item (Q_NULLPTR)
{
    mFh = new NcFramelessHelper;
    mFh->activateOn( this );
    mFh->useRubberBandOnMove(true);
    mFh->useRubberBandOnResize(true);

    settings = new QSettings();

    scene = new MainScene();
    setFileName(settings->value("filename").toString());

    m_mainview = new MainView(scene, this, settings);
    m_mainview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_mainview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_mainview->setBackgroundBrush(QBrush(QColor("#858e8e")));
    Sutton * openFileButton = new Sutton(this);
    openFileButton->setMainclr("#547a6b");
    openFileButton->setHoverclr("#39df9d");
    openFileButton->setSymbol(QChar(0xE712));
    QObject::connect(openFileButton, SIGNAL(clicked()), this, SLOT(openFile()));

    Sutton * collapseButton = new Sutton(this);
    collapseButton->setMainclr("#547a6b");
    collapseButton->setHoverclr("#39df9d");
    collapseButton->setSymbol(QChar(0xE972));
    QObject::connect(collapseButton, SIGNAL(clicked()), this, SLOT(switchPreview()));

    Sutton * quitButton = new Sutton(this);
    quitButton->setMainclr("#547a6b");
    quitButton->setHoverclr("#9e3d3d");
    quitButton->setSymbol(QChar(0xE711));

    QObject::connect(quitButton, SIGNAL(clicked()), this, SLOT(quitApp()));

    QSpacerItem *spaceritem1 = new QSpacerItem(marginAmount*1.5,
                                               marginAmount*1.5,
                                               QSizePolicy::Fixed,
                                               QSizePolicy::Fixed);
    QSpacerItem *spaceritem2 = new QSpacerItem(marginAmount*1.5,
                                               marginAmount*1.5,
                                               QSizePolicy::Fixed,
                                               QSizePolicy::Fixed);

    QHBoxLayout *hboxLayout = new QHBoxLayout();
    hboxLayout->addWidget(openFileButton, 0, Qt::AlignRight | Qt::AlignBottom);
    hboxLayout->addSpacerItem(spaceritem1);
    hboxLayout->addWidget(collapseButton, 0, Qt::AlignRight | Qt::AlignBottom);
    hboxLayout->addSpacerItem(spaceritem2);
    hboxLayout->addWidget(quitButton, 0, Qt::AlignRight | Qt::AlignBottom);
    hboxLayout->setSpacing(0);

    QHBoxLayout *hboxLayout1 = new QHBoxLayout();
    hboxLayout1->addWidget(m_mainview);
    hboxLayout1->setMargin(0);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(hboxLayout1);

    overlayWidget = new QWidget(centralWidget);
    overlayWidget->setLayout(hboxLayout);
    overlayWidget->setFixedSize(120,40);

    setCentralWidget(centralWidget);

    QWidget::setAttribute(Qt::WA_NativeWindow, true);

    // TODO: FIX this bullshit

    int minw, minh;

    minw = overlayWidget->width() + marginAmount*2;
    minh = overlayWidget->height() + marginAmount*2;

    setMinimumWidth(minw);
    setMinimumHeight(minh);

    QRect rect = QDesktopWidget().availableGeometry(this);

    int x0, y0, w, h;

    x0 = settings->value("windowX").toInt();
    y0 = settings->value("windowY").toInt();
    w = settings->value("windowWidth").toInt();
    h = settings->value("windowHeight").toInt();

    move(x0, y0);

    resize(QSize(max(w, minw), max(h, minh)));

    overlayWidget->move(width() - overlayWidget->width() - marginAmount, height() - overlayWidget->height() - marginAmount);
}

MainWindow::~MainWindow()
{
    delete m_mainview;
}

QString MainWindow::fileName()
{
    return m_filename;
}

void MainWindow::setFileName(QString value)
{
    QFile file (value);
    if (file.exists()) {

        qDebug(item == Q_NULLPTR ? "true": "false");
        if(item != Q_NULLPTR) scene->removeItem(item);
        settings->setValue("filename", value);

        file.open(QIODevice::ReadOnly);
        auto handler = new QPsdHandler();
        handler->setDevice(&file);
        handler->setFormat("psd");
        handler->read(&image);

        pix = QPixmap::fromImage(image);

        item = scene->addPixmap(pix);
    }
    else {
        qDebug("Error: file not exist.");
    }
}

void MainWindow::focusOutEvent (QFocusEvent *event)
{
    QCoreApplication::sendEvent(m_mainview,event);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    overlayWidget->move(width() - overlayWidget->width() - marginAmount, height() - overlayWidget->height() - marginAmount);
    QMainWindow::resizeEvent(event);
}

void MainWindow::quitApp()
{
    savePositionSettings();
    QApplication::quit();
}

void MainWindow::savePositionSettings()
{
    m_mainview->saveScroll();
    settings->setValue("windowX", this->frameGeometry().x());
    settings->setValue("windowY", this->frameGeometry().y());
    settings->setValue("windowWidth", this->frameGeometry().width());
    settings->setValue("windowHeight", this->frameGeometry().height());
}

void MainWindow::closeEvent(QCloseEvent *event) {
    Q_UNUSED(event)
    savePositionSettings();
}

void MainWindow::openFile() {
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,
                                            tr("Open Image"), "E:/Developement", tr("Image Files (*.png *.jpg *.bmp *.psd)")); //TODO: Save path
    if(fileName == "") return;
    setFileName(fileName);
}

void MainWindow::switchPreview()
{
    this->setPixmap(&pix,
                    this->frameGeometry().x() + this->frameGeometry().width()/2,
                    this->frameGeometry().y() + this->frameGeometry().height()/2); // passes center point
    this->hide();
}

void MainWindow::showMainWindow(int cx, int cy)
{
    this->show();
    this->setPositionCheck(cx - this->frameGeometry().width()/2,
                           cy - this->frameGeometry().height()/2);
}

void MainWindow::setPositionCheck(int cx, int cy)
{
    move(cx,cy);

    int newx, newy;

    qDebug() << "screenumber" << QDesktopWidget().screenNumber(this);
    int screenNumber = QDesktopWidget().screenNumber(this);
    QRect rect = QDesktopWidget().availableGeometry(screenNumber);
    int maxx = rect.x() + QDesktopWidget().screenGeometry(screenNumber).x();
    int maxy = rect.x() + QDesktopWidget().screenGeometry(screenNumber).y();

    if(cx + this->frameGeometry().width() > maxx)
        newx = rect.width() - this->frameGeometry().width();
    else
        newx = cx;

    if(cy + this->frameGeometry().height() > maxy)
        newy = rect.height() - this->frameGeometry().height();
    else
        newy = cy;

    move(newx, newy);

}
