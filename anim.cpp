#include "anim.h"

#include <QTimeLine>
#include <QDebug>

#include "mainpanel.h"

Lines::Animator::Animator(Lines::MainPanel *a_panel)
    : m_panel(a_panel)
{
    m_moveTimeLine = new QTimeLine(1000, this);
    m_moveTimeLine->setCurveShape(QTimeLine::LinearCurve);
    connect(m_moveTimeLine, SIGNAL(frameChanged(int)), SLOT(onMoveStep(int)));
    connect(m_moveTimeLine, SIGNAL(finished()), SIGNAL(moveFinished()));
    m_createTimeLine = new QTimeLine(1000, this);
    m_createTimeLine->setCurveShape(QTimeLine::LinearCurve);
    connect(m_createTimeLine, SIGNAL(frameChanged(int)), SLOT(onCreateStep(int)));
    connect(m_createTimeLine, SIGNAL(finished()), SIGNAL(createFinished()));
    m_removeTimeLine = new QTimeLine(1000, this);
    m_removeTimeLine->setCurveShape(QTimeLine::LinearCurve);
    connect(m_removeTimeLine, SIGNAL(frameChanged(int)), SLOT(onRemoveStep(int)));
    connect(m_removeTimeLine, SIGNAL(finished()), SIGNAL(removeFinished()));
}

bool Lines::Animator::isActive() const
{
    return m_moveTimeLine->state() == QTimeLine::Running ||
            m_createTimeLine->state() == QTimeLine::Running ||
            m_removeTimeLine->state() == QTimeLine::Running;
}

void Lines::Animator::startMove(Lines::Ball *ball, const QList<Cell> &path)
{
    m_ball = ball;
    m_path = path;
    int steps = path.count() - 1;
    m_moveTimeLine->setDuration(steps * 130);
    m_moveTimeLine->setFrameRange(0, steps * 5 - 1);
    m_moveTimeLine->setCurrentTime(0);
    m_moveTimeLine->start();
}

void Lines::Animator::startCreate(const QList<Lines::Ball *> &balls)
{
    m_balls = balls;
    m_createTimeLine->setDuration(700);
    m_createTimeLine->setFrameRange(0, 9);
    m_createTimeLine->setCurrentTime(0);
    m_createTimeLine->start();
}

void Lines::Animator::startRemove(const QList<Lines::Ball *> &balls)
{
    m_balls = balls;
    m_removeTimeLine->setDuration(1000);
    m_removeTimeLine->setFrameRange(0, 5);
    m_removeTimeLine->setCurrentTime(0);
    m_removeTimeLine->start();
}

Cell Lines::Animator::moveEndPoint()
{
    if(m_path.isEmpty())
        return Cell(-1, -1);
    return m_path.last();
}

QList<Lines::Ball *> Lines::Animator::balls()
{
    return m_balls;
}

void Lines::Animator::onMoveStep(int s)
{
    static int frames[6] = {0, 1, 2, 3, 2, 1};
    int s1 = s / 5;
    int s2 = s % 5;
    QPointF p1 = m_panel->fieldPoint(m_path[s1]);
    QPointF p2 = m_panel->fieldPoint(m_path[s1 + 1]);
    //qDebug() << p1 << " - " << p2;
    qreal r = qreal(s2) / 5.0;
    //m_ball->setMoveFrame(frames[s2]);
    m_ball->setPos(p1 + (p2 - p1) * r);
    //qDebug() << m_ball->pos();
}

void Lines::Animator::onCreateStep(int s)
{
    foreach(Lines::Ball *ball, m_balls)
    {
        ball->setBirthFrame(s);
        ball->show();
    }
}

void Lines::Animator::onRemoveStep(int s)
{
    foreach(Lines::Ball *ball, m_balls)
        ball->setXplodeFrame(s);
}
