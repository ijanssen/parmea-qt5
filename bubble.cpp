#include "bubble.h"

#include <QPainter>
#include <QTimeLine>
#include <QTimer>

Lines::Bubble::Bubble(QGraphicsItem *parent)
    : QGraphicsObject(parent)
{
    setOpacity(0.80);
    setZValue(300);

    QFont font("Arial");
    font.setPixelSize(24);
    font.setItalic(false);
    m_text = new QGraphicsTextItem(this);
    m_text->setFont(font);
    m_text->setDefaultTextColor(Qt::black);
    m_text->setTextWidth(80);
    m_text->setPos(10, 0);

    m_hideTimeLine = new QTimeLine(1000, this);
    m_hideTimeLine->setCurveShape(QTimeLine::LinearCurve);
    connect(m_hideTimeLine, SIGNAL(frameChanged(int)), SLOT(onHideFrameChanged(int)));
    connect(m_hideTimeLine, SIGNAL(finished()), SLOT(onHideFinished()));

    QTimer::singleShot(5000, this, SLOT(startHide()));
}

void Lines::Bubble::setText(const QString &text)
{
    m_text->setHtml(QString("<center>%1</center>").arg(text));
}

QRectF Lines::Bubble::boundingRect() const
{
    return QRectF(0, 0, 100, 40);
}

void Lines::Bubble::paint(QPainter *p, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QRectF r = boundingRect().adjusted(4.0, 4.0, -4.0, -4.0);
    p->setPen(Qt::darkGray);
    p->setBrush(QColor("#FFAAAA"));
    p->drawRoundedRect(r, 10.0, 10.0);
//    p->setPen(Qt::black);
//    QFont font("Arial");
//    font.setPixelSize(18);
//    p->setFont(font);
//    p->drawText(r.x(), r.bottom(), "Start Game");
}

void Lines::Bubble::startHide()
{
    if(m_hideTimeLine->state() == QTimeLine::Running)
        return;
    m_hideTimeLine->setDuration(1000);
    m_hideTimeLine->setFrameRange(7, 0);
    m_hideTimeLine->setCurrentTime(0);
    m_hideTimeLine->start();
}

void Lines::Bubble::onHideFrameChanged(int f)
{
    double o = 0.1 * double(f);
    setOpacity(o);
}

void Lines::Bubble::onHideFinished()
{
    delete this;
}
