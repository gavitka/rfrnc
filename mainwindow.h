#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QPixmap>
#include <QSettings>

class MainView;
class NcFramelessHelper;
class QWidget;
class MainScene;
class QGraphicsItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QString fileName();

    void setFileName(QString value);

signals:
    void fileNameChanged();
    void setPixmap(QPixmap*, int cx, int cy);

public slots:
    void quitApp();
    void openFile();
    void switchPreview();
    void showMainWindow(int,int);

private:

    MainView* m_mainview;
    NcFramelessHelper* mFh;
    QWidget* overlayWidget;

    QSettings *settings;
    QString m_filename;
    QImage image;
    QPixmap pix;
    QGraphicsItem *item;
    MainScene *scene;

    void focusOutEvent (QFocusEvent *event);
    void resizeEvent (QResizeEvent *event);
    void closeEvent(QCloseEvent *event);

    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;
    void savePositionSettings();
    void setPositionCheck(int cx, int cy);
    void leaveEvent(QEvent *event);
    void enterEvent(QEvent *event);
};

#endif // MAINWINDOW_H
