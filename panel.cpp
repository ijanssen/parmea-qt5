#include "panel.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QTimeLine>
#include <QLineEdit>
#include <QDebug>

QList<Lines::Panel *> Lines::Panel::m_panels;

Lines::Panel::Panel(QGraphicsItem *parent)
    : QGraphicsWidget(parent)
{
    setFlags(QGraphicsItem::ItemIsPanel);
    setPanelModality(QGraphicsItem::SceneModal);
    resize(this->boundingRect().size());
    hide();
    setOpacity(0.80);
    setZValue(100);
    m_hideTimeLine = new QTimeLine(1000, this);
    m_hideTimeLine->setCurveShape(QTimeLine::LinearCurve);
    connect(this, SIGNAL(visibleChanged()), SLOT(onVisibleChanged()));
    connect(m_hideTimeLine, SIGNAL(frameChanged(int)), SLOT(onHideFrameChanged(int)));
    connect(m_hideTimeLine, SIGNAL(finished()), SLOT(onHideFinished()));
    m_panels << this;
}

Lines::Panel::~Panel()
{
    m_panels.removeAll(this);
}

QRectF Lines::Panel::boundingRect() const
{
    return QRectF(0, 0, 360, 300);
}

void Lines::Panel::paint(QPainter *p, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rr = boundingRect().adjusted(4.0, 4.0, -4.0, -4.0);
    QRectF r = boundingRect().adjusted(10.0, 10.0, -10.0, -10.0);
    p->setPen(Qt::darkGray);
    p->setBrush(QColor("#FFFFFF"));
    p->drawRoundedRect(r, 30.0, 30.0);
    QPen dpen(Qt::white, 5, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin);
    p->setPen(dpen);
    p->setBrush(Qt::NoBrush);
    p->drawRoundedRect(rr, 30.0, 30.0);
}

QList<Lines::Panel *> Lines::Panel::visiblePanels()
{
    QList<Lines::Panel *> panels;
    foreach(Lines::Panel *panel, m_panels)
        if(panel->isVisible())
            panels << panel;
    return panels;
}

void Lines::Panel::startHide()
{
    if(m_hideTimeLine->state() == QTimeLine::Running)
        return;
    m_hideTimeLine->setDuration(600);
    m_hideTimeLine->setFrameRange(7, 0);
    m_hideTimeLine->setCurrentTime(0);
    m_hideTimeLine->start();
}

void Lines::Panel::onVisibleChanged()
{
    qDebug() << scene();
    if(isVisible() && scene())
        scene()->setActivePanel(this);
}

void Lines::Panel::onHideFrameChanged(int f)
{
    double o = 0.1 * double(f);
    setOpacity(o);
}

void Lines::Panel::onHideFinished()
{
    hide();
    setOpacity(0.80);
    emit closed();
}

Lines::LineEdit::LineEdit(QGraphicsItem *parent)
    : QGraphicsProxyWidget(parent)
{
    m_lineEdit = new QLineEdit();
    m_lineEdit->setStyleSheet("QLineEdit { background: white; \
                              color : black; \
                              font: bold 20px; \
                              border: 2px solid green; \
                              border-radius : 3px;}");
    //lineEdit->setFont(font);
    m_lineEdit->setMaxLength(10);
    //lineEdit->setText("Anonymous");
    setWidget(m_lineEdit);
}

QString	Lines::LineEdit::text() const
{
    return m_lineEdit->text();
}

void Lines::LineEdit::setText(const QString &text)
{
    m_lineEdit->setText(text);
}


Lines::PanelText::PanelText(QGraphicsItem *parent)
    : QGraphicsTextItem(parent)
{

}

QSizeF Lines::PanelText::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    return boundingRect().size();
}
