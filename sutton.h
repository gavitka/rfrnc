#ifndef SUTTON_H
#define SUTTON_H

#include <QWidget>

class QPaintEvent;

class Sutton : public QWidget
{
    Q_OBJECT
public:
    explicit Sutton(QWidget *parent = 0);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent*);
};

#endif // SUTTON_H
