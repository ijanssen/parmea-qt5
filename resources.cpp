#include "resources.h"

#include <QPixmap>
#include <QFile>
#include <QApplication>
#include <QDebug>
#include <QDir>

static const int help_pages_count = 5;

static const QString colornames[10] = {
    "Blue",
    "Green",
    "Orange",
    "Red",
    "Purple",
    "Yellow",
    "Black"};

Lines::Resources *Lines::Resources::self()
{
    static Lines::Resources m_resources;
    return &m_resources;
}

Lines::Resources::Resources(QObject *parent)
    : QObject(parent)
{
    //QDir path(QApplication::applicationDirPath());
    QDir path(QApplication::applicationFilePath());
    path.cdUp();
    m_path =  path.absolutePath() + "/assets/";
    qDebug() << "PATH: " << m_path;

    m_sounds[Music] = "music.mp3";
    m_sounds[Boom] = "boom.wav";
    m_sounds[Click] = "click.wav";

    m_splash = new QPixmap(imagesPath() + "splash.png");
}

int Lines::Resources::helpPagesCount() const
{
    return help_pages_count;
}

const QString Lines::Resources::imagesPath() const
{
    return path() + "images_854x480/";
}

const QString Lines::Resources::soundsPath() const
{
    return path() + "sounds/";
}

const QString Lines::Resources::langPath() const
{
    return path() + "lang/";
}

QPixmap *Lines::Resources::spheres(int c) const
{
    return m_spheres[c - 1];
}

QPixmap *Lines::Resources::splash() const
{
    return m_splash;
}

QPixmap *Lines::Resources::spheresSelected(int c, int f) const
{
    return m_spheresSelected[c - 1][f];
}

QPixmap *Lines::Resources::spheresBirth(int c, int f) const
{
    return m_spheresBirth[c - 1][f];
}

QPixmap *Lines::Resources::spheresMove(int c, int f) const
{
    return m_spheresMove[c - 1][f];
}

QPixmap *Lines::Resources::spheresXplode(int c, int f) const
{
    return m_spheresXplode[c - 1][f];
}

QPixmap *Lines::Resources::spheresBoom(int c) const
{
    return m_spheresBoom[c - 1];
}

QPixmap *Lines::Resources::field() const
{
    return m_field;
}

QPixmap *Lines::Resources::fieldHighlighted() const
{
    return m_fieldHighlighted;
}

QPixmap *Lines::Resources::fieldZoomed() const
{
    return m_fieldZoomed;
}

QPixmap *Lines::Resources::backgroundPortrait() const
{
    return m_backgroundPortrait;
}

QPixmap *Lines::Resources::backgroundLandscape() const
{
    return m_backgroundLandscape;
}

QPixmap *Lines::Resources::icon(IconType n) const
{
    return m_icons[n];
}

QByteArray *Lines::Resources::svgButton(int n) const
{
    return m_button[n];
}

const QString &Lines::Resources::help(int p) const
{
    return m_help[p];
}

const QString Lines::Resources::sound(int n) const
{
    if (m_sounds.contains(n))
        return soundsPath() + m_sounds[n];
    return QString();
}

QByteArray *Lines::Resources::getFromFile(const QString &name)
{
    QFile file(name);
    if (!file.open(QFile::ReadOnly))
        return 0;
    QByteArray *t = new QByteArray(file.readAll());
    return t;
}

void Lines::Resources::init()
{
    qDebug() << "init res " << imagesPath();

    m_backgroundPortrait = new QPixmap(imagesPath() + "backgroundp.png");
    m_backgroundLandscape = new QPixmap(imagesPath() + "backgroundl.png");

    m_field = new QPixmap(imagesPath() + "field.png");
    m_fieldHighlighted = new QPixmap(imagesPath() + "fieldh.png");
    m_fieldZoomed = new QPixmap(imagesPath() + "fieldz.png");

    m_button[0] = getFromFile(imagesPath() + "btn_01.svg");
    m_button[1] = getFromFile(imagesPath() + "btn_02.svg");
    m_button[2] = getFromFile(imagesPath() + "btn_03.svg");
    m_button[3] = getFromFile(imagesPath() + "btn_04.svg");
    m_button[4] = getFromFile(imagesPath() + "btn_05.svg");
    m_button[5] = getFromFile(imagesPath() + "btn_06.svg");
    m_button[6] = getFromFile(imagesPath() + "btn_07.svg");
    m_button[7] = getFromFile(imagesPath() + "btn_muted.svg");

    m_icons[Quit] = new QPixmap(imagesPath() + "icoQuit.png");
    m_icons[Undo] = new QPixmap(imagesPath() + "icoUndo.png");
    m_icons[SoundOff] = new QPixmap(imagesPath() + "icoSoundOff.png");
    m_icons[SoundOn] = new QPixmap(imagesPath() + "icoSoundOn.png");
    m_icons[HiScores] = new QPixmap(imagesPath() + "icoHiScores.png");
    m_icons[Help] = new QPixmap(imagesPath() + "icoHelp.png");
    m_icons[NewGame] = new QPixmap(imagesPath() + "icoNewGame.png");
    m_icons[Preview] = new QPixmap(imagesPath() + "icoPreview.png");
    m_icons[Count3] = new QPixmap(imagesPath() + "icoCount3.png");
    m_icons[Count4] = new QPixmap(imagesPath() + "icoCount4.png");
    m_icons[Count5] = new QPixmap(imagesPath() + "icoCount5.png");

    for(int c = 0; c < Lines::ColorsNumber; c++)
    {
        m_spheres[c] = new QPixmap(QString(imagesPath() + "s%1Normal.png")
                                    .arg(colornames[c]));
        for (int n = 0; n < 3; n++)
        {
            QString num = QString::number(n + 1).rightJustified(2, '0');
            m_spheresSelected[c][n] = new QPixmap(QString(imagesPath() + "s%1Select%2.png")
                                        .arg(colornames[c])
                                        .arg(num));
        }
        for (int n = 0; n < 10; n++)
        {
            QString num = QString::number(n + 1).rightJustified(2, '0');
            m_spheresBirth[c][n] = new QPixmap(QString(imagesPath() + "s%1Birth%2.png")
                                        .arg(colornames[c])
                                        .arg(num));
        }
        for (int n = 0; n < 7; n++)
        {
            QString num = QString::number(n + 1).rightJustified(2, '0');
            m_spheresMove[c][n] = new QPixmap(QString(imagesPath() + "s%1Move%2.png")
                                        .arg(colornames[c])
                                        .arg(num));
        }
        for (int n = 0; n < 6; n++)
        {
            QString num = QString::number(n + 1).rightJustified(2, '0');
            m_spheresXplode[c][n] = new QPixmap(QString(imagesPath() + "s%1Xplode%2.png")
                                        .arg(colornames[c])
                                        .arg(num));
        }
        m_spheresBoom[c] = new QPixmap(QString(imagesPath() + "s%1Boom.png")
                                    .arg(colornames[c]));
    }
    initHelp();
    qDebug() << "ok res";
    emit inited();
}

void Lines::Resources::initHelp()
{
    QString img = QString("<img src=\"%1i\\1.png\" />").arg(imagesPath());
    QString path = QApplication::applicationDirPath() + "/lang/";
    QString locale = QLocale::system().name();
    for(int p = 0; p < helpPagesCount(); p++)
    {
        QString fn = langPath() + QString("help_ru_%1.html").arg(p + 1);
        qDebug() << fn;
        //if(!QFile::exists(fn))
            //fn = QString(":/lang/help_en.html");
        QByteArray *help = getFromFile(fn);
        if(!help)
            break;
        QString str = QString(*help);
        delete help;
        str.replace(QRegExp("\\[I([0-9]+)\\]"), img);
        str.replace(QRegExp("\\[VER\\]"), Lines::TextVersion);
        m_help << str;
        //qDebug() << str;
    }
}
