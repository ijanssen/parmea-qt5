#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsWidget>

class QTimeLine;
class QSvgRender;

namespace Lines
{

class Button : public QGraphicsWidget
{
    Q_OBJECT
public:
    Button(QGraphicsItem *parent = 0);
    virtual ~Button();

    void setText(const QString &text);
    void setIcon(QPixmap *icon, QPoint p = QPoint(0, 0));

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);

signals:
    void pressed();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *);
    void resizeEvent(QGraphicsSceneResizeEvent *event);

private slots:
    void onFrameChanged(int f);

private:
    QPixmap *m_icon;
    QString m_text;
    QPoint m_iconPoint;
    QTimeLine *m_pressTimeLine;
    int m_curFrame;
    QImage *m_images[8];
};

};

#endif // BUTTON_H
