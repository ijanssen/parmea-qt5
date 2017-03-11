#ifndef INFOPANEL_H
#define INFOPANEL_H

#include <QGraphicsItem>

#include "ball.h"

namespace Lines
{

class InfoPanel : public QGraphicsItem
{
public:
    explicit InfoPanel(QGraphicsItem *parent = 0);

    void setNextColors(const QVector<Lines::Ball::Color>  &nextColors);
    void setScore(int score);
    void setOrientation(bool orientation);
    void setShowNext(bool b);
    void setShowScore(bool b);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *p, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
private:
    QVector<Lines::Ball::Color>  m_nextColors;
    int m_score;
    // true - portrait
    // false - landscape
    bool m_orientation;
    bool m_showNext;
    bool m_showScore;
};

};

#endif // INFOPANEL_H
