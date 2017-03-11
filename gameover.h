#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "panel.h"

namespace Lines
{

class LineEdit;
class Button;

class GameOver : public Lines::Panel
{
    Q_OBJECT
public:
    GameOver(QGraphicsItem *parent = 0);

    virtual QRectF boundingRect() const;

    // false - without High Score
    // true - with High Score
    bool mode() const;
    void setMode(bool b, QString name = QString());
    bool result() const;
    QString name() const;

private slots:
    void onButtonClick();

private:
    bool               m_mode;
    bool               m_result;
    int                m_height;
    QGraphicsTextItem *m_hstext;
    Lines::LineEdit   *m_lineEdit;
    Lines::Button     *m_okBtn;
    Lines::Button     *m_cancelBtn;
};

};

#endif // GAMEOVER_H
