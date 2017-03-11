#ifndef BOOM_H
#define BOOM_H

#include <QObject>
#include <QVector>
#include <QPointF>

#include "ball.h"

class QGraphicsPixmapItem;
class QGraphicsItem;
class QTimeLine;

namespace Lines
{

class Boom : public QObject
{
    Q_OBJECT
public:
    explicit Boom(Lines::Ball::Color aColor, QGraphicsItem *parent = 0);
    ~Boom();

    void start(const QPointF &center);

private slots:
    void onFrameChanged(int s);
    void onFinished();

private:
    QVector<QGraphicsPixmapItem *> m_items;
    QPointF m_center;
    QTimeLine *m_moveTimeLine;
};

};

#endif // BOOM_H
