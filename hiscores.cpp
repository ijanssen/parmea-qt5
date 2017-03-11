#include "hiscores.h"

#include <QPainter>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextTable>
#include <QSettings>
#include <QDebug>

#include "button.h"

const int Lines::HiScores::Scores = 8;

Lines::HiScores::HiScores(QGraphicsItem *parent)
    : Lines::Panel(parent)
    , m_lastName(tr("Anonymous"))
{
    m_text = new QGraphicsTextItem("tt", this);
    Lines::Button *okBtn = new Lines::Button(this);
    okBtn->setText(tr("Ok"));
    okBtn->resize(60, 60);
    okBtn->setPos(130, 230);
    m_text->setTextWidth(360 - 40);
    m_text->setPos(20, 20);
    connect(okBtn, SIGNAL(pressed()), SLOT(onButtonClick()));
    updateText();
}

QString Lines::HiScores::lastName() const
{
    return m_lastName;
}

void Lines::HiScores::setLastName(const QString &lastName)
{
    m_lastName = lastName;
}

void Lines::HiScores::loadConfig(QSettings &settings)
{
    settings.beginGroup("HiScore");
    int count = settings.value("Count", 0).toInt();
    m_lastName = settings.value("LastName", m_lastName).toString();
    for(int idx = 0; idx < count; idx++)
    {
        QString name = settings.value(QString("Name%1").arg(idx), "Anonymous").toString();
        int score = settings.value(QString("Score%1").arg(idx), 0).toInt();
        addScore(name, score);
    }
    settings.endGroup();
    updateText();
}

void Lines::HiScores::saveConfig(QSettings &settings)
{
    settings.beginGroup("HiScore");
    settings.setValue("Count", m_scores.count());
    settings.setValue("LastName", m_lastName);
    int idx = 0;
    foreach (const Score &score, m_scores)
    {
        settings.setValue(QString("Name%1").arg(idx), score.name);
        settings.setValue(QString("Score%1").arg(idx), score.score);
        idx++;
    }
    settings.endGroup();
}

void Lines::HiScores::addNewScore(const QString &name, int score)
{
    if(!canAdd(score))
        return;
    addScore(name, score);
    updateText();
}

bool Lines::HiScores::canAdd(int score)
{
    if(score <= 0)
        return false;
    if(m_scores.count() < Scores)
        return true;
    if(m_scores.last().score < score)
        return true;
    return false;
}

void Lines::HiScores::addScore(const QString &name, int score)
{
    while(m_scores.count() >= Scores)
        m_scores.removeLast();
    Score s;
    s.name = name;
    s.score = score;
    //m_scores << s;
    QList<Score>::Iterator it = m_scores.begin();
    for(; it != m_scores.end(); it++)
        if((*it).score < score)
        {
            qDebug() << (*it).score;
            m_scores.insert(it, s);
            return;
        }
    m_scores.insert(it, s);
}

void Lines::HiScores::onButtonClick()
{
    startHide();
}

void Lines::HiScores::updateText()
{
    m_text->setDefaultTextColor(Qt::black);
    QFont font("Arial");
    font.setPixelSize(18);
    font.setBold(true);
    font.setItalic(true);
    ////
    QTextCharFormat nameFormat;
    nameFormat.setFont(font);
    //nameFormat.setAlignment(Qt::AlignRight);
    ////
    QTextCharFormat scoreFormat;
    scoreFormat.setFont(font);
    ////
    m_text->document()->clear();
    QTextCursor cur = m_text->textCursor();
    QTextTableFormat orderTableFormat;
    orderTableFormat.setWidth(QTextLength(QTextLength::PercentageLength, 100));
    QVector<QTextLength> cons(3);
    cons[0] = QTextLength();
    cons[1] = QTextLength(QTextLength::FixedLength, 100);
    cons[2] = QTextLength(QTextLength::FixedLength, 80);
    orderTableFormat.setColumnWidthConstraints(cons);
    orderTableFormat.setBorderStyle(QTextFrameFormat::BorderStyle_None);
    orderTableFormat.setAlignment(Qt::AlignCenter);
    QTextTable *table = cur.insertTable(m_scores.count(), 3, orderTableFormat);
    int r = 0;
    foreach(const Score &score, m_scores)
    {
        QTextTableCell cell = table->cellAt(r, 0);
        cell.setFormat(nameFormat);
        cur = cell.firstCursorPosition();
        //cur.block().se;
        cur.insertText(score.name);
        ////
        cell = table->cellAt(r, 1);
        cell.setFormat(scoreFormat);
        cur = cell.firstCursorPosition();
        cur.insertText("....................");
        ////
        cell = table->cellAt(r, 2);
        cell.setFormat(scoreFormat);
        cur = cell.firstCursorPosition();
        QString s = QString::number(score.score).rightJustified(6, '0');
        cur.insertText(s);
        r++;
    }
}
