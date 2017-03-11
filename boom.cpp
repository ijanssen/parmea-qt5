#include "boom.h"

#include <QGraphicsPixmapItem>
#include <QTimeLine>
#include <QBrush>
#include <QDebug>
#include <cmath>

#include "resources.h"

static const int BoomPieces = 15;

Lines::Boom::Boom(Lines::Ball::Color aColor, QGraphicsItem *parent)
{
    m_items.resize(BoomPieces);
    for(int i = 0; i < BoomPieces; i++)
    {
        QGraphicsPixmapItem *item = new QGraphicsPixmapItem(parent);
        item->setZValue(1000.0);
        item->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
        item->setPixmap(*Lines::Resources::self()->spheresBoom(aColor));
        m_items[i] = item;
    }
    m_moveTimeLine = new QTimeLine(1000, this);
    m_moveTimeLine->setCurveShape(QTimeLine::LinearCurve);
    connect(m_moveTimeLine, SIGNAL(frameChanged(int)), SLOT(onFrameChanged(int)));
    connect(m_moveTimeLine, SIGNAL(finished()), SLOT(onFinished()));
}

Lines::Boom::~Boom()
{
    qDebug() << "delete boom";
    for(int i = 0; i < BoomPieces; i++)
        delete m_items[i];
}

void Lines::Boom::start(const QPointF &center)
{
    m_center = center;
    for(int i = 0; i < BoomPieces; i++)
    {
        double a = 2.0 * M_PI * double(i) / double(BoomPieces);
        double x = 10.0 * cos(a);
        double y = 10.0 * sin(a);
        m_items[i]->setPos(m_center + QPointF(x, y));
        m_items[i]->show();
    }
   m_moveTimeLine->setDuration(700);
    m_moveTimeLine->setFrameRange(0, 39);
    m_moveTimeLine->setCurrentTime(0);
    m_moveTimeLine->start();
}

void Lines::Boom::onFrameChanged(int s)
{
    for(int i = 0; i < BoomPieces; i++)
    {
        double a = 2.0 * M_PI * double(i) / double(BoomPieces);
        double x = 7.0 * cos(a);
        double y = 7.0 * sin(a);
        m_items[i]->setPos(m_items[i]->pos() + QPointF(x, y));
        //m_items[i]->moveBy(x, y);
        double o = double(39 - s) / 39.0;
        m_items[i]->setOpacity(o);
    }
}

void Lines::Boom::onFinished()
{
    delete this;
    //for(int i = 0; i < 30; i++)
    //    m_items[i]->hide();
}
