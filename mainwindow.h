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

public slots:
    void quitApp();
    void openFile();

private:

    MainView* m_mainview;
    NcFramelessHelper* mFh;
    QWidget* overlayWidget;
    MainScene *scene;

    QSettings settings;
    QString m_filename;
    QImage image;
    QPixmap pix;
    QGraphicsItem *item;

    void focusOutEvent (QFocusEvent *event);
    void resizeEvent (QResizeEvent *event);
    void closeEvent(QCloseEvent *event);

    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;
    void savePositionSettings();
};

#endif // MAINWINDOW_H
