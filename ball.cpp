#include "ball.h"

#include "resources.h"
#include "platform.h"

#include <QGraphicsSceneMouseEvent>
#include <QTimeLine>
#include <QDebug>

Lines::Ball::Color Lines::Ball::randomColor()
{
    //return (Lines::Ball::Color)(3);
    return (Lines::Ball::Color)(rand() % 7 + 1);
}

Lines::Ball::Ball(Color color)
    : QGraphicsPixmapItem()
    , m_fieldX(-1)
    , m_fieldY(-1)
    , QObject(0)
    , m_color(color)
{
    hide();
    //translate(Lines::BallImgTransX, Lines::BallImgTransY);
    setTransform(QTransform::fromTranslate(Lines::BallImgTransX, Lines::BallImgTransY), true);
    setPixmap(*Lines::Resources::self()->spheres(m_color));
    m_selectTimeLine = new QTimeLine(1000, this);
    m_selectTimeLine->setCurveShape(QTimeLine::LinearCurve);
    m_selectTimeLine->setLoopCount(0);
    m_selectTimeLine->setDuration(400);
    m_selectTimeLine->setFrameRange(0, 3);
    connect(m_selectTimeLine, SIGNAL(frameChanged(int)), SLOT(updateFrame(int)));
    //connect(m_selectTimeLine, SIGNAL(finished()), SLOT(slot1()));

}

Cell Lines::Ball::cell() const
{
    Cell c(m_fieldX, m_fieldY);
    return c;
}

void Lines::Ball::setField(int x, int y)
{
    m_fieldX = x;
    m_fieldY = y;
}

void Lines::Ball::setColor(Color color)
{
    m_color = color;
    setPixmap(*Lines::Resources::self()->spheres(m_color));
}

void Lines::Ball::setFrame(int f)
{
    f = f % 4;
    if (f == 3)
        setPixmap(*Lines::Resources::self()->spheres(m_color));
    else
        setPixmap(*Lines::Resources::self()->spheresSelected(m_color, f));
}

void Lines::Ball::setBirthFrame(int f)
{
    setPixmap(*Lines::Resources::self()->spheresBirth(m_color, f));
}

void Lines::Ball::setMoveFrame(int f)
{
    f %= 7;
    setPixmap(*Lines::Resources::self()->spheresMove(m_color, f));
}

void Lines::Ball::setXplodeFrame(int f)
{
    setPixmap(*Lines::Resources::self()->spheresXplode(m_color, f));
}

void Lines::Ball::select()
{
    m_selectTimeLine->setCurrentTime(0);
    m_selectTimeLine->start();
}

void Lines::Ball::deselect()
{
    m_selectTimeLine->stop();
    setFrame(7);
}

void Lines::Ball::updateFrame(int f)
{
    setFrame(f);
}
