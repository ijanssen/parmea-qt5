#include "splashscreen.h"

#include <QDebug>

// needed for S60-specific orientation/softkey handling
#ifdef Q_WS_S60
#include <coemain.h>
#include <aknappui.h>
#endif

Lines::SplashScreen::SplashScreen(const QPixmap &pixmap) :
    QSplashScreen(pixmap, Qt::WindowStaysOnTopHint)
{
}

Lines::SplashScreen::~SplashScreen()
{
    //qDebug() << "splash destroy";
}

void Lines::SplashScreen::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}

// Lock S60 app orientation to portrait - used when showing the splash screen
void Lines::SplashScreen::lockPortraitOrientation()
{
#ifdef Q_WS_S60
    CAknAppUi* s60AppUi = dynamic_cast<CAknAppUi*> (CCoeEnv::Static()->AppUi());
    // save the old orientation
    m_orientation = (int)s60AppUi->Orientation();
    TRAP_IGNORE(
        if (s60AppUi) {
        // Lock portrait orientation when showing the splash screen
        s60AppUi->SetOrientationL(CAknAppUi::EAppUiOrientationPortrait);
    });
#endif
    //setAttribute(Qt::WA_LockPortraitOrientation, true);
}


// Releases the orientation lock (restores previous orientation)
void Lines::SplashScreen::releaseOrientation()
{
    // do nothing if orientation is not locked
    if( m_orientation == -1 )
        return;

#ifdef Q_WS_S60
    CAknAppUi* s60AppUi = dynamic_cast<CAknAppUi*> (CCoeEnv::Static()->AppUi());

    TRAP_IGNORE(
        if (s60AppUi) {
        s60AppUi->SetOrientationL((CAknAppUiBase::TAppUiOrientation)m_orientation);
    });
#endif
}
