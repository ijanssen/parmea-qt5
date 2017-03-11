#ifndef SOUND_H
#define SOUND_H

#include <QObject>
#include <QMediaPlayer>

QT_USE_NAMESPACE

namespace Lines
{

class Sound : public QObject
{
    Q_OBJECT
public:
    static Sound *self();

    explicit Sound(QObject *parent = 0);

    void init(int volume, bool soundOn);

    void play(int n);

    void musicSet(const QString &file);
    void musicPlay();
    void musicStop();

    void volumeUp();
    void volumeDown();

    void soundOn();
    void soundOff();

private slots:
    void onStateChanged(QMediaPlayer::State state);

private:
    QMediaPlayer *createPlayer(int n);

private:
    int m_volume;
    bool m_soundOn;
    bool m_musicOn;
    QMap<int, QMediaPlayer *> m_players;
    QMediaPlayer *m_musicPlayer;
};
}

#endif // SOUND_H
