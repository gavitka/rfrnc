#ifndef MAINVIEW_H
#define MAINVIEW_H
#include <QGraphicsView>
#include <QPoint>
#include <QTime>

class QGraphicsScene;
class QMouseEvent;
class QSettings;

class MainView : public QGraphicsView
{
    Q_OBJECT

    Q_PROPERTY(int scale READ scale WRITE setScale)

public:
    MainView(QGraphicsScene *scene, QWidget *parent = Q_NULLPTR, QSettings *settingsValues = Q_NULLPTR);
    int scale() {return m_scale;}
    void setScale(int value);
    QSettings *settings;

    void rememberScroll();
    void saveScroll();

signals:

    void setPixmap(QPixmap* pixmap);

private:

    void mousePressEvent(QMouseEvent * e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void focusOutEvent ( QFocusEvent * event );
    void wheelEvent(QWheelEvent *event);
    bool event(QEvent * event);

    bool m_scrolling;
    bool m_selected;

    qreal m_scaleFactor;
    int m_scale;

    QPoint m_mousePressViewPoint;
    QPoint m_clickStartPoint;
    QTime time;
};

#endif // MAINVIEW_H
