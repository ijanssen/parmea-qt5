#ifndef HELP_H
#define HELP_H

#include "panel.h"

namespace Lines
{
class Button;

class Help : public Lines::Panel
{
    Q_OBJECT
public:
    explicit Help(QGraphicsItem *parent = 0);

    virtual QRectF boundingRect() const;

private slots:
    void onCloseButtonClicked();
    void onPrevButtonClicked();
    void onNextButtonClicked();

private:
    void updatePage();

private:
    QGraphicsTextItem *m_text;
    QGraphicsTextItem *m_pageText;
    Lines::Button *m_closeButton;
    int m_page;
};

};

#endif // HELP_H
