#include "infopanel.h"

#include <QPainter>

#include "ball.h"
#include "resources.h"
#include "platform.h"

Lines::InfoPanel::InfoPanel(QGraphicsItem *parent)
    : QGraphicsItem(parent)
    , m_nextColors(3)
    , m_score(0)
    , m_orientation(true)
    , m_showNext(true)
    , m_showScore(true)
{
    m_nextColors[0] = Lines::Ball::Red;
    m_nextColors[1] = Lines::Ball::Green;
    m_nextColors[2] = Lines::Ball::Blue;
}

void Lines::InfoPanel::setNextColors(const QVector<Lines::Ball::Color>  &nextColors)
{
    m_nextColors = nextColors;
    update();
}

void Lines::InfoPanel::setScore(int score)
{
    m_score = score;
    update();
}

void Lines::InfoPanel::setOrientation(bool orientation)
{
    m_orientation = orientation;
    update();
}

void Lines::InfoPanel::setShowNext(bool b)
{
    m_showNext = b;
    update();
}

void Lines::InfoPanel::setShowScore(bool b)
{
    m_showScore = b;
    update();
}

QRectF Lines::InfoPanel::boundingRect() const
{
    if(m_orientation)
        return QRectF(0, 0, Lines::InfoPanelSizeXP, Lines::InfoPanelSizeYP);
    else
        return QRectF(0, 0, Lines::InfoPanelSizeXL, Lines::InfoPanelSizeYL);
}

void Lines::InfoPanel::paint(QPainter *p, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //p->fillRect(boundingRect(), QBrush(Qt::cyan));
    if(m_showNext)
    {
        int x, y;
        if(m_orientation)
        {
            x = Lines::InfoPanelNextPosXP;
            y = Lines::InfoPanelNextPosYP;
        }
        else
        {
            x = Lines::InfoPanelNextPosXL;
            y = Lines::InfoPanelNextPosYL;
        }
        if(m_nextColors.count() > 0)
            p->drawPixmap(x + 10, y, *Lines::Resources::self()->spheres(m_nextColors[0]));
        if(m_nextColors.count() > 1)
            p->drawPixmap(x + 60, y, *Lines::Resources::self()->spheres(m_nextColors[1]));
        if(m_nextColors.count() > 2)
            p->drawPixmap(x + 110, y, *Lines::Resources::self()->spheres(m_nextColors[2]));
    }
    if(m_showScore)
    {
        int x;
        if(m_orientation)
            x = 34;
        else
            x = 76;
        QString score = QString::number(m_score).rightJustified(6, '0');
        p->setPen(Qt::black);
        QFont font("Arial");
        font.setBold(true);
        font.setItalic(true);
        font.setPixelSize(Lines::InfoPanelFontSize);
        p->setPen(Qt::white);
        p->setFont(font);
        p->drawText(x, 40, score);
    }
}
