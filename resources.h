#ifndef RESOURCES_H
#define RESOURCES_H

#include <QObject>
#include <QMap>

#include "globals.h"

class QPixmap;

namespace Lines
{

class Resources : public QObject
{
    Q_OBJECT
public:
    enum IconType {Quit = 0,
                    Undo = 1,
                    SoundOff = 2,
                    SoundOn = 3,
                    HiScores = 4,
                    Help = 5,
                    NewGame = 6,
                    Preview = 7,
                    Count3 = 8,
                    Count4 = 9,
                    Count5 = 10};
    enum SoundType { Music = 0,
                     Boom = 1,
                   Click = 2};

    static Resources *self();

    explicit Resources(QObject *parent = 0);

    int helpPagesCount() const;

    const QString path() const {return m_path; }
    const QString imagesPath() const;
    const QString soundsPath() const;
    const QString langPath() const;

    void init();
    void initHelp();

    QPixmap *splash() const;

    QPixmap *spheres(int c) const;
    QPixmap *spheresSelected(int c, int f) const;
    QPixmap *spheresBirth(int c, int f) const;
    QPixmap *spheresMove(int c, int f) const;
    QPixmap *spheresXplode(int c, int f) const;
    QPixmap *spheresBoom(int c) const;

    QPixmap *field() const;
    QPixmap *fieldHighlighted() const;
    QPixmap *fieldZoomed() const;
    QPixmap *backgroundPortrait() const;
    QPixmap *backgroundLandscape() const;
    QPixmap *icon(IconType n) const;
    QByteArray *svgButton(int n) const;

    const QString &help(int p) const;

    const QString sound(int n) const;

signals:
    void inited();

private:
    QByteArray *getFromFile(const QString &name);

private:
    QString m_path;

    QPixmap *m_splash;
    QPixmap *m_spheres[Lines::ColorsNumber];
    QPixmap *m_spheresSelected[Lines::ColorsNumber][3];
    QPixmap *m_spheresBirth[Lines::ColorsNumber][10];
    QPixmap *m_spheresMove[Lines::ColorsNumber][7];
    QPixmap *m_spheresXplode[Lines::ColorsNumber][6];
    QPixmap *m_spheresBoom[Lines::ColorsNumber];
    QPixmap *m_field;
    QPixmap *m_fieldHighlighted;
    QPixmap *m_fieldZoomed;
    QPixmap *m_backgroundPortrait;
    QPixmap *m_backgroundLandscape;
    QPixmap *m_icons[11];
    QByteArray *m_button[8];
    QList<QString> m_help;

    QMap<int, QString> m_sounds;
};

};

#endif // RESOURCES_H
