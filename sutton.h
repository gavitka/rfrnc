#ifndef SUTTON_H
#define SUTTON_H

#include <QWidget>
#include <QColor>
#include <QPushButton>


class QPaintEvent;

class Sutton : public QPushButton
{
    Q_OBJECT

    Q_PROPERTY(QColor mainclr READ mainclr WRITE setMainclr NOTIFY mainclrChanged)
public: QColor mainclr() const {return m_mainclr; }
public: void setMainclr(QColor value) {m_mainclr = value; }
signals: void mainclrChanged();
private: QColor m_mainclr;

    Q_PROPERTY(QColor hoverclr READ hoverclr WRITE setHoverclr NOTIFY hoverclrChanged)
public: QColor hoverclr() const {return m_hoverclr; }
public: void setHoverclr(QColor value) {m_hoverclr = value; }
signals: void hoverclrChanged();
private: QColor m_hoverclr;

    Q_PROPERTY(QChar symbol READ symbol WRITE setSymbol NOTIFY symbolChanged)
public: QChar symbol() const {return m_symbol; }
public: void setSymbol(QChar value) {m_symbol = value; }
signals: void symbolChanged();
private: QChar m_symbol;

public:
    explicit Sutton(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent*);

private:
    QColor* m_currentclr;
    QColor m_pressclr;
    QColor* m_textcurrentclr;
    QColor m_textclr;
    QColor m_textpressclr;
    void enterEvent(QEvent * event);
    void leaveEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // SUTTON_H
