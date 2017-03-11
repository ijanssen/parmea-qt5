#include "sound.h"

#include <QApplication>
#include <QMediaPlayer>
#include <QFile>
#include <QDebug>
#include <QSound>

#include "resources.h"

Lines::Sound *Lines::Sound::self()
{
    static Lines::Sound m_sound;
    return &m_sound;
}


Lines::Sound::Sound(QObject *parent) :
    QObject(parent)
{
    m_volume = 50;
    m_soundOn = true;
    m_musicOn = false;
    //////
    m_musicPlayer = new QMediaPlayer();
    //qDebug() << "volume = " << m_musicPlayer->volume();
    //m_musicPlayer->setVolume(m_volume);
    //connect(m_player, SIGNAL(stateChanged(QMediaPlayer::State)), SLOT(onStateChanged(QMediaPlayer::State)));
}

void Lines::Sound::init(int volume, bool soundOn)
{
    m_volume = volume;
    m_soundOn = soundOn;
    m_musicPlayer->setVolume(m_volume);
    QMap<int, QMediaPlayer *>::const_iterator it = m_players.constBegin();
    while (it != m_players.constEnd())
    {
        it.value()->setVolume(m_volume);
        ++it;
    }
}

void Lines::Sound::play(int n)
{
    if (!m_soundOn)
        return;
    QMediaPlayer *player = createPlayer(n);
    player->play();
}

void Lines::Sound::musicSet(const QString &file)
{
    m_musicPlayer->setMedia(QUrl::fromLocalFile(file));
}

void Lines::Sound::musicPlay()
{
    m_musicOn = true;
    if (!m_soundOn)
        return;
    m_musicPlayer->play();
}

void Lines::Sound::musicStop()
{
    m_musicOn = false;
    m_musicPlayer->stop();
}

void Lines::Sound::volumeUp()
{
    m_volume += 10;
    if (m_volume > 100)
        m_volume = 100;
    m_musicPlayer->setVolume(m_volume);
    QMap<int, QMediaPlayer *>::const_iterator it = m_players.constBegin();
    while (it != m_players.constEnd())
    {
        it.value()->setVolume(m_volume);
        ++it;
    }
}

void Lines::Sound::volumeDown()
{
    m_volume -= 10;
    if (m_volume < 0)
        m_volume = 0;
    m_musicPlayer->setVolume(m_volume);
    QMap<int, QMediaPlayer *>::const_iterator it = m_players.constBegin();
    while (it != m_players.constEnd())
    {
        it.value()->setVolume(m_volume);
        ++it;
    }
}

void Lines::Sound::soundOn()
{
    m_soundOn = true;
    if(m_musicOn)
        m_musicPlayer->play();
}

void Lines::Sound::soundOff()
{
    m_soundOn = false;
    m_musicPlayer->stop();
}

void Lines::Sound::onStateChanged(QMediaPlayer::State state)
{

    qDebug() << state;
}

QMediaPlayer *Lines::Sound::createPlayer(int n)
{
    if (m_players.contains(n))
        return m_players[n];
    QMediaPlayer *player = new QMediaPlayer();
    //qDebug() << "volume = " << player->volume();
    player->setVolume(m_volume);
    connect(player, SIGNAL(stateChanged(QMediaPlayer::State)), SLOT(onStateChanged(QMediaPlayer::State)));
    player->setMedia(QUrl::fromLocalFile(Lines::Resources::self()->sound(n)));
    m_players[n] = player;
    return player;
}
