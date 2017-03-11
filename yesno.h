#ifndef YESNO_H
#define YESNO_H

#include "panel.h"

class QGraphicsTextItem;

namespace Lines
{

class YesNo : public Lines::Panel
{
    Q_OBJECT
public:
    explicit YesNo(QGraphicsItem *parent = 0);

    virtual QRectF boundingRect() const;

    void setText(const QString &text);
    bool result() const {return m_result;}

private slots:
    void onButtonClick();

private:
    QGraphicsTextItem *m_text;
    bool m_result;
};

};

#endif // YESNO_H
