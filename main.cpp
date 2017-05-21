#include "mainwindow.h"
#include "circlepreview.h"
#include <QApplication>
#include <QCoreApplication>
#include <QPixmap>

#define QT_NO_MENUBAR

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("khSoft");
    QCoreApplication::setApplicationName("Capisco");

    MainWindow w;
    CirclePreview c;

    QObject::connect(&c,SIGNAL(showMainWindow(int,int)),&w,SLOT(showMainWindow(int,int)));
    QObject::connect(&w,SIGNAL(setPixmap(QPixmap*,int,int)),&c,SLOT(setPixmap(QPixmap*,int,int)));

    //QObject::connect(quitButton, SIGNAL(clicked()), this, SLOT(quitApp()));

    w.show();

    return a.exec();
}
