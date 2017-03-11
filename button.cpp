#include "button.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneResizeEvent>
#include <QTimeLine>
#include <QSvgRenderer>
#include <QDebug>

#include "resources.h"
#include "sound.h"

//QSvgRender *Lines::Button::m_svgRenders[8] = {0, 0, 0, 0, 0, 0, 0, 0};

Lines::Button::Button(QGraphicsItem *parent)
    : QGraphicsWidget(parent)
    , m_icon(0)
    , m_curFrame(0)
{
    setAcceptHoverEvents(false);
    setCacheMode(DeviceCoordinateCache);
    for(int n = 0; n < 8; n++)
        m_images[n] = 0;
    m_pressTimeLine = new QTimeLine(QTimeLine::LinearCurve, this);
    m_pressTimeLine->setDuration(700);
    m_pressTimeLine->setFrameRange(0, 6);
    m_pressTimeLine->setCurrentTime(0);
    connect(m_pressTimeLine, SIGNAL(frameChanged(int)), SLOT(onFrameChanged(int)));
}

Lines::Button::~Button()
{
    for(int n = 0; n < 8; n++)
        if(m_images[n])
            delete m_images[n];
}

void Lines::Button::setText(const QString &text)
{
    m_text = text;
}

void Lines::Button::setIcon(QPixmap *icon, QPoint p)
{
    m_icon = icon;
    m_iconPoint = p;
}

void Lines::Button::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    if(!m_text.isEmpty())
    {
        QFont font("Arial");
        font.setPixelSize(20);
        font.setItalic(true);
        painter->setFont(font);
        painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, m_text);
    }
    if(m_icon)
        painter->drawPixmap(m_iconPoint, *m_icon);
    if(isEnabled())
        painter->drawImage(0, 0, *m_images[m_curFrame]);
    else
        painter->drawImage(0, 0, *m_images[7]);
}

void Lines::Button::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    //update();
}

void Lines::Button::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    //update();
    qDebug() << "release " << isEnabled();
    Sound::self()->play(Lines::Resources::Click);
    if (!isEnabled())
        return;
    emit pressed();
    if (m_pressTimeLine->state() != QTimeLine::Running)
        m_pressTimeLine->start();
}

void Lines::Button::resizeEvent(QGraphicsSceneResizeEvent *event)
{
    QGraphicsWidget::resizeEvent(event);
    QSizeF s = event->newSize();
    QSvgRenderer render;
    for(int n = 0; n < 8; n++)
    {
        render.load(*Lines::Resources::self()->svgButton(n));
        QImage *img = new QImage(s.toSize(), QImage::Format_ARGB32);
        img->fill(0);
        QPainter painter(img);
        render.render(&painter, QRectF(QPointF(0, 0), s));
        if (m_images[n])
            delete m_images[n];
        m_images[n] = img;
    }
}

void Lines::Button::onFrameChanged(int f)
{
    m_curFrame = (f + 1) % 7;
    update();
}
