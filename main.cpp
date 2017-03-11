#include <QApplication>
#include <QTranslator>
#include <QTextCodec>
#include <QLocale>
#include <QDebug>

#include <cstdlib>
#include <ctime>

#include "build.h"
#include "globals.h"
#include "platform.h"
#include "view.h"
#include "splashscreen.h"
#include "resources.h"

int main(int argc, char *argv[])
{
    srand((unsigned)time(0));
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QApplication a(argc, argv);

    QString locale = QLocale::system().name();
    qDebug() << "locale: " << locale;
    QTranslator translator;
    translator.load(QString(":/lang/lines_%1.qm").arg(locale));
    a.installTranslator(&translator);

    Lines::SplashScreen *splash = new Lines::SplashScreen(*Lines::Resources::self()->splash());

    splash->lockPortraitOrientation();
    splash->showFullScreen();
    splash->raise();

    Lines::Resources::self()->init();

    Lines::View w;
#ifdef DESKTOP_P
    w.setFixedSize(Lines::Height, Lines::Width);
    w.show();
#endif
#ifdef DESKTOP_L
    w.setFixedSize(Lines::Width, Lines::Height);
    w.show();
#endif
#ifdef PHONE
    w.showFullScreen();
#endif

    //splash->releaseOrientation();
    delete splash;

    return a.exec();
}
