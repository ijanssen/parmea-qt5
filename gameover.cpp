#include "gameover.h"

#include <QLineEdit>
#include <QGraphicsProxyWidget>

#include "button.h"

Lines::GameOver::GameOver(QGraphicsItem *parent)
    : Panel(parent)
{
    m_height = 310;
    QGraphicsTextItem *text = new QGraphicsTextItem(this);
    text->setHtml(QString("<center><font size=+3><b>%1</b></font></center><center>%2</center>")
                  .arg(tr("Game Over"))
                  .arg(tr("Try play again!")));
    QFont font("Arial");
    font.setPixelSize(20);
    font.setItalic(true);
    text->setFont(font);
    text->setDefaultTextColor(Qt::black);
    text->setTextWidth(320);
    text->setPos(20, 20);

    m_hstext = new QGraphicsTextItem(this);
    m_hstext->setHtml(tr("You can be at <b>High Scores</b>! Enter your name."));
    QFont font2("Arial");
    font2.setPixelSize(20);
    font2.setItalic(false);
    m_hstext->setFont(font2);
    m_hstext->setDefaultTextColor(Qt::black);
    m_hstext->setTextWidth(320);


    m_lineEdit = new Lines::LineEdit(this);
    m_lineEdit->resize(320, 40);

    m_okBtn = new Lines::Button(this);
    m_okBtn->resize(90, 90);
    m_okBtn->setText(tr("Add"));
    m_okBtn->setData(0, QVariant(1));
    m_cancelBtn = new Lines::Button(this);
    m_cancelBtn->resize(90, 90);
    m_cancelBtn->setText(tr("Cancel"));
    m_cancelBtn->setData(0, QVariant(2));
    connect(m_okBtn, SIGNAL(pressed()), SLOT(onButtonClick()));
    connect(m_cancelBtn, SIGNAL(pressed()), SLOT(onButtonClick()));
}

QRectF Lines::GameOver::boundingRect() const
{
    return QRectF(0, 0, 360, m_height);
}

bool Lines::GameOver::mode() const
{
    return m_mode;
}

void Lines::GameOver::setMode(bool b, QString name)
{
    m_mode = b;
    if(m_mode)
    {
        m_hstext->show();
        m_lineEdit->show();
        m_cancelBtn->show();
        m_hstext->setPos(20, 100);
        m_lineEdit->setPos(20, 160);
        m_okBtn->setPos(80, 206);
        m_cancelBtn->setPos(210, 206);
        m_height = 310;
        m_lineEdit->setText(name);
    }
    else
    {
        m_hstext->hide();
        m_lineEdit->hide();
        m_cancelBtn->hide();
        m_okBtn->setPos(135, 100);
        m_okBtn->setText(tr("Ok"));
        m_height = 210;
    }
}

bool Lines::GameOver::result() const
{
    return m_result;
}

QString Lines::GameOver::name() const
{
    return m_lineEdit->text();
}

void Lines::GameOver::onButtonClick()
{
    Lines::Button *btn = qobject_cast<Lines::Button *>(sender());
    if(btn->data(0).toInt() == 1)
        m_result = true;
    else
        m_result = false;
    startHide();
}
