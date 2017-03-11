#ifndef BUBBLE_H
#define BUBBLE_H

#include <QGraphicsObject>

class QGraphicsTextItem;
class QTimeLine;

namespace Lines
{

class Bubble : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit Bubble(QGraphicsItem *parent);

    void setText(const QString &text);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *p, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

signals:
    void closed();

private slots:
    void startHide();
    void onHideFrameChanged(int f);
    void onHideFinished();

private:
    QGraphicsTextItem *m_text;
    QTimeLine *m_hideTimeLine;
};

}

#endif // BUBBLE_H
