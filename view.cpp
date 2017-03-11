#include "view.h"

#include <QGraphicsScene>
#include <QResizeEvent>
#include <QTimer>
#include <QDebug>

#include "build.h"
#include "ball.h"
#include "scene.h"
#include "sound.h"

#ifdef Q_WS_S60

// A private class to access Symbian RemCon API
class MediakeyCaptureItemPrivate : public QObject, public MRemConCoreApiTargetObserver
{
public:
    MediakeyCaptureItemPrivate(Lines::View *parent);
    ~MediakeyCaptureItemPrivate();
    virtual void MrccatoCommand(TRemConCoreApiOperationId aOperationId,
                                            TRemConCoreApiButtonAction aButtonAct);
private:
    CRemConInterfaceSelector* iInterfaceSelector;
    CRemConCoreApiTarget*     iCoreTarget;
    Lines::View *d_ptr;
};

// Constructor
MediakeyCaptureItemPrivate::MediakeyCaptureItemPrivate(Lines::View *parent): d_ptr(parent)
{
    QT_TRAP_THROWING(iInterfaceSelector = CRemConInterfaceSelector::NewL());
    QT_TRAP_THROWING(iCoreTarget = CRemConCoreApiTarget::NewL(*iInterfaceSelector, *this));
    iInterfaceSelector->OpenTargetL();
}

// Destructor
MediakeyCaptureItemPrivate::~MediakeyCaptureItemPrivate(){
    delete iInterfaceSelector;
    delete  iCoreTarget;
}

// Callback when media keys are pressed
void MediakeyCaptureItemPrivate::MrccatoCommand(TRemConCoreApiOperationId aOperationId,
                                        TRemConCoreApiButtonAction aButtonAct)
{
    //TRequestStatus status;
    switch( aOperationId )
    {
    case ERemConCoreApiVolumeUp:
        d_ptr->volumeUpPressed();
        break;
    case ERemConCoreApiVolumeDown:
        d_ptr->volumeDownPressed();
        break;
    default:
        break;
    }
}
#endif // Q_WS_S60

#ifdef Q_OS_UNIX
#include <QX11Info>
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#endif

enum ScreenOrientation
{
    Landscape = 0,
    Portrait = 270,
    LandscapeInverted = 180,
    PortraitInverted = 90
};

static void writeX11OrientationAngleProperty(QWidget* widget, ScreenOrientation orientation = Portrait)
{
#ifdef Q_WS_X11
    if (widget) {
        WId id = widget->winId();
        Display *display = QX11Info::display();
        if (!display) return;
        Atom orientationAngleAtom = XInternAtom(display, "_MEEGOTOUCH_ORIENTATION_ANGLE", False);
        XChangeProperty(display, id, orientationAngleAtom, XA_CARDINAL, 32, PropModeReplace, (unsigned char*)&orientation, 1);
    }
#endif
}


Lines::View::View(QWidget *parent)
    : QGraphicsView(parent)
{
#ifdef Q_WS_S60
    new MediakeyCaptureItemPrivate(this);
#endif

    //writeX11OrientationAngleProperty(this, Portrait);

    //this->rotate(270);
    //t(0, 0, 480, 854);

    setCacheMode(QGraphicsView::CacheBackground);
    setCacheMode(QGraphicsView::CacheNone);
    setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    setFrameStyle(QFrame::NoFrame);
    setOptimizationFlags( QGraphicsView::DontClipPainter |
                                    QGraphicsView::DontSavePainterState |
                                    QGraphicsView::DontAdjustForAntialiasing );
    m_scene = new Lines::Scene();
    setScene(m_scene);
    m_scene->resize(480, 854);

    connect(m_scene, SIGNAL(closed()), SLOT(close()));
#ifdef DEMO_2MIN
    m_dieTimer = new QTimer(this);
    m_dieTimer->setSingleShot(true);
    connect(m_dieTimer, SIGNAL(timeout()), SLOT(close()));
    m_dieTimer->start(1000 * 120);
#endif
}

void Lines::View::volumeUpPressed()
{
    qDebug() << "Key +";
    Sound::self()->volumeUp();
}

void Lines::View::volumeDownPressed()
{
    qDebug() << "Key -";
    Sound::self()->volumeDown();
}

void Lines::View::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    //m_scene->resize(event->size().width(), event->size().height());
    m_scene->resize(480, 854);
}
