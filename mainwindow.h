#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QImage;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QImage * mainImage;
};

#endif // MAINWINDOW_H
