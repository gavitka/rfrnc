#include "mainwindow.h"
#include <QApplication>
#include <QCoreApplication>

#define QT_NO_MENUBAR

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("khSoft");
    QCoreApplication::setApplicationName("Capisco");

    MainWindow w;
    w.show();

    return a.exec();
}
