#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

#include "globals.h"
#include "ball.h"
#include "mainpanel.h"

class QTimeLine;
class QSound;

namespace Lines
{
class Button;
class InfoPanel;
class Scene;
class Panel;
class HiScores;

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    Scene();

    void resize(int w, int h);

signals:
    void closed();

private:
    Lines::MainPanel *m_mainPanel;
};

};
#endif // SCENE_H
