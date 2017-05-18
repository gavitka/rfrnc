#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainView;
class QImage;
class NcFramelessHelper;
class QWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QImage * mainImage;

private:

    MainView* m_mainview;
    NcFramelessHelper* mFh;
    QWidget* overlayWidget;

    void focusOutEvent (QFocusEvent *event);
    void resizeEvent(QResizeEvent *event);

    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;
    void openFile();
};

#endif // MAINWINDOW_H
