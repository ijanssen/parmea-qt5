#include "yesno.h"

#include <QTextDocument>
#include <QTextCursor>
#include <QDebug>

#include "button.h"

Lines::YesNo::YesNo(QGraphicsItem *parent)
    : Panel(parent)
    , m_result(false)
{
    QFont font("Arial");
    font.setPixelSize(26);
    font.setItalic(true);
    m_text = new QGraphicsTextItem(this);
    m_text->setFont(font);
    m_text->setDefaultTextColor(Qt::black);
    m_text->setTextWidth(340);
    m_text->setPos(10, 30);

    Lines::Button *yBtn = new Lines::Button(this);
    yBtn->setData(0, QVariant(1));
    yBtn->setText(tr("Yes"));
    yBtn->resize(90, 90);
    Lines::Button *nBtn = new Lines::Button(this);
    nBtn->setData(0, QVariant(2));
    nBtn->setText(tr("No"));
    nBtn->resize(90, 90);

    yBtn->setPos(80, 80);
    nBtn->setPos(210, 80);

    connect(yBtn, SIGNAL(pressed()), SLOT(onButtonClick()));
    connect(nBtn, SIGNAL(pressed()), SLOT(onButtonClick()));
}

QRectF Lines::YesNo::boundingRect() const
{
    return QRectF(0, 0, 360, 180);
}

void Lines::YesNo::setText(const QString &text)
{
    m_text->setHtml(QString("<center>%1</center>").arg(text));
}

void Lines::YesNo::onButtonClick()
{
    Lines::Button *btn = qobject_cast<Lines::Button *>(sender());
    if(btn->data(0).toInt() == 1)
        m_result = true;
    else
        m_result = false;
    startHide();
}
