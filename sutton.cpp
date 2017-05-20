#include "sutton.h"
#include <QPainter>
#include <QRectF>
#include <QPointF>
#include <QFont>
#include <QFontDatabase>
#include <QDebug>

Sutton::Sutton(QWidget *parent) :
    QPushButton(parent),
    m_pressclr (QColor("white")),
    m_textclr (QColor("white")),
    m_textpressclr (QColor("black"))
{
    setMinimumSize(30,30);
    m_currentclr = &m_mainclr;
    m_textcurrentclr = &m_textclr;

    setMainclr(QColor("#547a6b"));
    setHoverclr(QColor("#39df9d"));
    setSymbol(QChar(0xE89C));

    QFontDatabase fontDB;
//    fontDB.addApplicationFont("qrc:/segoe-mdl2-assets.ttf");
    QFontDatabase::addApplicationFont("qrc:/segoe-mdl2-assets.ttf");
//    foreach(QString s, fontDB.families())
//    {
//        qDebug() << s;
//    }
}

void Sutton::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);

    QPainter painter(this);
    QPen pen(Qt::NoPen);

    QBrush brush(*m_currentclr);

    painter.setBrush(brush);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawEllipse(rect());

    QFont font("Segoe MDL2 Assets",12,QFont::Normal);
    QPointF point;
    point.setX(rect().x());
    point.setY(rect().y());

    QPen penHText(*m_textcurrentclr);
    painter.setFont(font);
    painter.setPen(penHText);

    painter.drawText(rect(), Qt::AlignCenter, m_symbol);
}

void Sutton::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    m_currentclr = &m_hoverclr;
    repaint();
}

void Sutton::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    m_currentclr = &m_mainclr;
    repaint();
}

void Sutton::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_currentclr = &m_pressclr;
    m_textcurrentclr = &m_textpressclr;
    repaint();

    QPushButton::mousePressEvent(event);
}

void Sutton::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_currentclr = &m_hoverclr;
    m_textcurrentclr = &m_textclr;
    repaint();

    QPushButton::mouseReleaseEvent(event);
}
