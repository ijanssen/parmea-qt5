#ifndef HISCORES_H
#define HISCORES_H

#include "panel.h"

class QSettings;

namespace Lines
{

class HiScores : public Panel
{
    Q_OBJECT
public:
    static const int Scores;
    explicit HiScores(QGraphicsItem *parent = 0);
    virtual ~HiScores() {}

    QString lastName() const;
    void setLastName(const QString &lastName);

    void loadConfig(QSettings &settings);
    void saveConfig(QSettings &settings);

    void addNewScore(const QString &name, int score);
    bool canAdd(int score);

private slots:
    void onButtonClick();

private:
    void addScore(const QString &name, int score);
    void updateText();

private:
    QGraphicsTextItem *m_text;
    struct Score
    {
        QString name;
        int score;
    };
    QList<Score> m_scores;
    QString m_lastName;
};

};


#endif // HISCORES_H
