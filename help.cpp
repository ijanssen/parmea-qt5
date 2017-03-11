#include "help.h"

#include "button.h"
#include "resources.h"

Lines::Help::Help(QGraphicsItem *parent)
    : Lines::Panel(parent)
    , m_page(0)
{
    QFont f1("Verdana");
    f1.setPixelSize(16);
    f1.setBold(false);
    m_text = new QGraphicsTextItem(this);
    m_text->setFont(f1);
    m_text->setDefaultTextColor(Qt::black);
    m_text->setTextWidth(360 - 40);
    m_text->setPos(20, 20);

    QFont f2("Arial");
    f2.setPixelSize(20);
    f2.setBold(true);
    m_pageText = new QGraphicsTextItem(this);
    m_pageText->setFont(f2);
    m_pageText->setDefaultTextColor(Qt::black);
    m_pageText->setPos(100, 410);

    m_closeButton = new Lines::Button(this);
    m_closeButton->resize(80, 80);
    m_closeButton->setText(tr("Ok"));
    m_closeButton->setPos(260, 390);
    //m_closeButton->setIcon(Lines::Resources::self()->icon(Lines::Resources::Preview));

    Lines::Button *m_prevBtn = new Lines::Button(this);
    m_prevBtn->resize(50, 50);
    m_prevBtn->setText(tr("<"));
    m_prevBtn->setPos(40, 400);
    Lines::Button *m_nextBtn = new Lines::Button(this);
    m_nextBtn->resize(50, 50);
    m_nextBtn->setText(tr(">"));
    m_nextBtn->setPos(140, 400);

    updatePage();

    connect(m_closeButton, SIGNAL(pressed()), SLOT(onCloseButtonClicked()));
    connect(m_prevBtn, SIGNAL(pressed()), SLOT(onPrevButtonClicked()));
    connect(m_nextBtn, SIGNAL(pressed()), SLOT(onNextButtonClicked()));
}

QRectF Lines::Help::boundingRect() const
{
    return QRectF(0, 0, 360, 480);
}

void Lines::Help::onCloseButtonClicked()
{
    startHide();
}

void Lines::Help::onPrevButtonClicked()
{
    if(m_page == 0)
        return;
    m_page--;
    updatePage();
}

void Lines::Help::onNextButtonClicked()
{
    if(m_page == Lines::Resources::self()->helpPagesCount() - 1)
        return;
    m_page++;
    updatePage();
}

void Lines::Help::updatePage()
{
    m_text->setHtml(Lines::Resources::self()->help(m_page));
    m_pageText->setHtml(QString("<b>%1/%2</b>").arg(m_page + 1)
                        .arg(Lines::Resources::self()->helpPagesCount()));
}
