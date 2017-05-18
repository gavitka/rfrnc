#ifndef SUTTON_H
#define SUTTON_H

#include <QWidget>
#include <QColor>

class QPaintEvent;

class Sutton : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor mainclr READ mainclr WRITE setMainclr NOTIFY mainclrChanged)

public:
    explicit Sutton(QWidget *parent = 0);
    QColor mainclr() const {
        return m_mainclr;
    }
    void setMainclr(QColor value) {
        m_mainclr = value;
    }

signals:
    void mainclrChanged();


public slots:

protected:
    void paintEvent(QPaintEvent*);

private:
    QColor m_mainclr;
};

#endif // SUTTON_H
