#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>

class QGraphicsScene;
class QTimer;

#ifdef Q_WS_S60
#include <remconcoreapitargetobserver.h>    // link against RemConCoreApi.lib
#include <remconcoreapitarget.h>            // and
#include <remconinterfaceselector.h>        // RemConInterfaceBase.lib
#endif // Q_WS_S60

namespace Lines
{
class Scene;

class View : public QGraphicsView
{
    Q_OBJECT
public:
    View(QWidget *parent = 0);

    void volumeUpPressed();
    void volumeDownPressed();

protected:
    void resizeEvent(QResizeEvent *event);


private:
    Lines::Scene *m_scene;
    QTimer *m_dieTimer;
};

}

#endif // VIEW_H
