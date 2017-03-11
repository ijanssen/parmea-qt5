#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <QObject>

#include "globals.h"
class QTimeLine;

namespace Lines
{
class MainPanel;
class Ball;

class Animator : public QObject
{
	Q_OBJECT
public:
	Animator(Lines::MainPanel *a_panel);

	bool isActive() const;

	void startMove(Lines::Ball *ball, const QList<Cell> &path);
	void startCreate(const QList<Lines::Ball *> &balls);
	void startRemove(const QList<Lines::Ball *> &balls);
	Cell moveEndPoint();
	QList<Lines::Ball *> balls();

signals:
	void moveFinished();
	void createFinished();
	void removeFinished();

private slots:
	void onMoveStep(int s);
	void onCreateStep(int s);
	void onRemoveStep(int s);

private:
	Lines::MainPanel *m_panel;
	QTimeLine *m_moveTimeLine;
	QTimeLine *m_createTimeLine;
	QTimeLine *m_removeTimeLine;
	Lines::Ball *m_ball;
	QList<Cell> m_path;
	QList<Lines::Ball *> m_balls;
};

};

#endif // ANIMATOR_H
