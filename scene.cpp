#include "scene.h"

#include <QtGlobal>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QTimeLine>
#include <QSound>

#include <QDebug>

#include "ball.h"
#include "button.h"
#include "infopanel.h"
#include "gameover.h"
#include "yesno.h"
#include "hiscores.h"
#include "resources.h"

/*
Lines::Animator::Animator(Lines::Scene *a_scene)
    : m_scene(a_scene)
{
    m_moveTimeLine = new QTimeLine(QTimeLine::LinearCurve, this);
    connect(m_moveTimeLine, SIGNAL(frameChanged(int)), SLOT(onMoveStep(int)));
    connect(m_moveTimeLine, SIGNAL(finished()), SIGNAL(moveFinished()));
    m_createTimeLine = new QTimeLine(QTimeLine::LinearCurve, this);
    connect(m_createTimeLine, SIGNAL(frameChanged(int)), SLOT(onCreateStep(int)));
    connect(m_createTimeLine, SIGNAL(finished()), SIGNAL(createFinished()));
    m_removeTimeLine = new QTimeLine(QTimeLine::LinearCurve, this);
    connect(m_removeTimeLine, SIGNAL(frameChanged(int)), SLOT(onRemoveStep(int)));
    connect(m_removeTimeLine, SIGNAL(finished()), SIGNAL(removeFinished()));
}

bool Lines::Animator::isActive() const
{
    return m_moveTimeLine->state() == QTimeLine::Running;
}

void Lines::Animator::startMove(Lines::Ball *ball, const QList<Cell> &path)
{
    m_ball = ball;
    m_path = path;
    int steps = path.count() - 1;
    m_moveTimeLine->setDuration(steps * 100);
    m_moveTimeLine->setFrameRange(0, steps * 10 - 1);
    m_moveTimeLine->setCurrentTime(0);
    m_moveTimeLine->start();
}

void Lines::Animator::startCreate(const QList<Lines::Ball *> &balls)
{
    m_balls = balls;
    m_createTimeLine->setDuration(400);
    m_createTimeLine->setFrameRange(0, 4);
    m_createTimeLine->setCurrentTime(0);
    m_createTimeLine->start();

}

void Lines::Animator::startRemove()
{
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
    int s1 = s / 10;
    int s2 = s % 10;
    QPointF p1 = m_scene->fieldPoint(m_path[s1]);
    QPointF p2 = m_scene->fieldPoint(m_path[s1 + 1]);
    //qDebug() << p1 << " - " << p2;
    qreal r = qreal(s2) / 10.0;
    m_ball->setFrame(s2);
    m_ball->setPos(p1 + (p2 - p1) * r);
}

void Lines::Animator::onCreateStep(int s)
{
    qDebug() << "sss " << s << m_balls.count();
    foreach(Lines::Ball *ball, m_balls)
    {
        ball->setFrame(s + 10);
        ball->show();
    }
}

void Lines::Animator::onRemoveStep(int s)
{
}
*/


Lines::Scene::Scene()
{
    /*QGraphicsPixmapItem *splash = new QGraphicsPixmapItem(*Lines::Resources::self()->splash());
    splash->setPos(0, 0);
    splash->setZValue(5000);
    addItem(splash);
    splash->show();*/

    m_mainPanel = new Lines::MainPanel();
    addItem(m_mainPanel);
    connect(m_mainPanel, SIGNAL(closed()), SIGNAL(closed()));
    m_mainPanel->show();
}

void Lines::Scene::resize(int w, int h)
{
    setSceneRect(0, 0, w, h);

    m_mainPanel->resize(w, h);
}

//void Lines::Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
//{
//	QGraphicsScene::mousePressEvent(event);
//	if(m_animator->isActive() || !m_gameActive)
//		return;
//	if (!m_fieldRect.contains(event->scenePos().toPoint()))
//		return;
//	//qDebug() << event->scenePos();
//	//qDebug() << itemAt(event->scenePos());
//	if(m_selected)
//	{
//		Cell to = point2cell(event->scenePos().toPoint());
//		if(getBall(to))
//			m_zoomedField->hide();
//		else
//			showZoomedField(to);
//	}
//}

//void Lines::Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
//{
//	QGraphicsScene::mouseReleaseEvent(event);
//	if(m_animator->isActive() || !m_gameActive)
//		return;
//	if (!m_fieldRect.contains(event->scenePos().toPoint()))
//		return;
//	QGraphicsItem *item = itemAt(event->scenePos());
//	Lines::Ball *ball = dynamic_cast<Lines::Ball *>(item);
//	if(ball)
//	{
//		if(m_selected)
//			m_selected->deselect();
//		m_selected = ball;
//		m_selected->select();
//		return;
//	}
//	if(m_selected)
//	{
//		Cell to = point2cell(event->scenePos().toPoint());
//		m_zoomedField->hide();
//		//qDebug() << to;
//		Cell from = m_selected->cell();
//		QList<Cell> path;
//		bool r = findPath(from, to, path);
//		if(r)
//		{
//			m_animator->startMove(m_selected, path);
//			m_selected->deselect();
//		}
//	}
//}

//void Lines::Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
//{
//	QGraphicsScene::mouseMoveEvent(event);
//	if(m_animator->isActive() || !m_gameActive)
//		return;
//	if (!m_fieldRect.contains(event->scenePos().toPoint()))
//		return;
//	if(m_selected)
//	{
//		Cell to = point2cell(event->scenePos().toPoint());
//		if(getBall(to))
//			m_zoomedField->hide();
//		else
//			showZoomedField(to);
//	}
//}

//void Lines::Scene::drawBackground(QPainter *painter, const QRectF &rect)
//{
//	int x = m_fieldRect.x();
//	int y = m_fieldRect.y();
//	for(int i = 0; i < Lines::CellsNumber; i++)
//		for(int j = 0; j < Lines::CellsNumber; j++)
//			painter->drawPixmap(x + j * m_cellSize, y + i * m_cellSize, m_cellSize, m_cellSize, *Lines::Resources::self()->field());
//}

//void Lines::Scene::endTurn()
//{
//	QList<Lines::Ball *> balls;
//	bool b = placeNewBalls(balls);
//	if (b)
//	{
//		m_gameActive = false;
//		//m_msgGameOver->show();
//		qDebug() << m_hiScores->minScore();
//		if(m_hiScores->minScore() < m_score)
//			m_hiScores->addScore("Vasya", m_score);
//		return;
//	}
//	m_animator->startCreate(balls);
//}

//void Lines::Scene::onMoveFinished()
//{
//	Cell to = m_animator->moveEndPoint();
//	placeBall(m_selected, to.first, to.second);
//	m_selected = 0;
//	bool b = findLines();
//	if(!b)
//		endTurn();
//}

//void Lines::Scene::onCreateFinished()
//{
//	foreach(Lines::Ball *ball, m_animator->balls())
//		ball->setFrame(6);
//	createNewBalls();
//}

//void Lines::Scene::onRemoveFinished()
//{
//}

//void Lines::Scene::startNewGame()
//{
//	m_selected = 0;
//	for(int i = 0; i < Lines::CellsNumber; i++)
//		for(int j = 0; j < Lines::CellsNumber; j++)
//		{
//			if(m_fields[i][j])
//				delete m_fields[i][j];
//			m_fields[i][j] = 0;
//		}
//	m_freeCells = Lines::CellsNumber * Lines::CellsNumber;
//	m_score = 0;
//	m_infoPanel->setScore(0);
//	m_gameActive = true;

//	createNewBalls();
//	endTurn();
//}

//void Lines::Scene::showHiScores()
//{
//	m_hiScores->show();
//	//m_hiScores->setPanelModality(QGraphicsItem::PanelModal);
//	setActivePanel(m_hiScores);
//}

//void Lines::Scene::onGameOver()
//{
//	/*Lines::GameOver *m_gameOver = new Lines::GameOver();
//	addItem(m_gameOver);
//	m_gameOver->show();
//	setActivePanel(m_gameOver);*/
//	Lines::YesNo *yesno = new Lines::YesNo();
//	addItem(yesno);
//	yesno->show();
//	setActivePanel(yesno);
//}

//void Lines::Scene::createNewBalls()
//{
//	for (int i = 0; i < 3; i++)
//		m_newColors[i] = Lines::Ball::randomColor();
//	m_infoPanel->setNextColors(m_newColors);
//}

//bool Lines::Scene::placeNewBalls(QList<Lines::Ball *> &balls)
//{
//	QList<Cell> freecells;
//	for(int y = 0; y < Lines::CellsNumber; y++)
//		for(int x = 0; x < Lines::CellsNumber; x++)
//			if(!m_fields[y][x])
//				freecells << Cell(x, y);
//	for(int i = 0; i < 3; i++)
//		if(freecells.count() > 0)
//		{
//			int r = rand() % freecells.count();
//			Cell c = freecells.takeAt(r);
//			Lines::Ball *ball = new Lines::Ball(m_newColors[i]);
//			placeBall(ball, c.first, c.second);
//			balls << ball;
//		}
//	if(freecells.count() == 0)
//	{
//		qDebug() << "game over";
//		return true;
//	}
//	return false;
//}

//QPoint Lines::Scene::fieldPoint(int x, int y) const
//{
//	QPoint p(m_cellSize * x, m_cellSize * y);
//	p += m_fieldRect.topLeft();
//	return p;
//}

//Cell Lines::Scene::point2cell(const QPoint &p) const
//{
//	Cell c(-1, -1);
//	if(!m_fieldRect.contains(p))
//		return c;
//	QPoint pp = p - m_fieldRect.topLeft();
//	c.first = pp.x() / m_cellSize;
//	c.second = pp.y() / m_cellSize;
//	return c;
//}

//void Lines::Scene::placeBall(Lines::Ball *ball, int x, int y)
//{
//	if(m_fields[y][x])
//		return;
//	if(ball->fieldX() != -1 && ball->fieldY() != -1)
//		m_fields[ball->fieldY()][ball->fieldX()] = 0;
//	ball->setField(x, y);
//	m_fields[y][x] = ball;
//	if(!ball->scene())
//		addItem(ball);
//	updateBall(ball);
//}

//void Lines::Scene::updateBall(Lines::Ball *ball)
//{
//	ball->setPos(fieldPoint(ball->fieldX(), ball->fieldY()));
//}

//Lines::Ball *Lines::Scene::getBall(const Cell &cell) const
//{
//	return m_fields[cell.second][cell.first];
//}

//void Lines::Scene::showZoomedField(const Cell &cell)
//{
//	QPoint pc = fieldPoint(cell);
//	m_zoomedField->setPos(pc - QPoint(20, 20));
//	m_zoomedField->show();
//}

//bool Lines::Scene::findPath(const Cell &from, const Cell &to, QList<Cell> &path)
//{
//	QList<Cell> queue;
//	int Q[Lines::CellsNumber][Lines::CellsNumber];
//	QMap<Cell, Cell> P;
//	for(int y = 0; y < Lines::CellsNumber; y++)
//		for(int x = 0; x < Lines::CellsNumber; x++)
//			Q[y][x] = -1;

//	queue << from;
//	Q[from.second][from.first] = 0;

//	while(true)
//	{
//		if(queue.isEmpty())
//		{
//			break;
//		}
//		Cell c = queue.takeFirst();
//		if(c.first > 0 && Q[c.second][c.first - 1] == -1 && !m_fields[c.second][c.first - 1])
//		{
//			Q[c.second][c.first - 1] = Q[c.second][c.first] + 1;
//			queue << Cell(c.first - 1, c.second);
//			P[Cell(c.first - 1, c.second)] = c;
//		}
//		if(c.first < Lines::CellsNumber - 1 && Q[c.second][c.first + 1] == -1 && !m_fields[c.second][c.first + 1])
//		{
//			Q[c.second][c.first + 1] = Q[c.second][c.first] + 1;
//			queue << Cell(c.first + 1, c.second);
//			P[Cell(c.first + 1, c.second)] = c;
//		}
//		if(c.second > 0 && Q[c.second - 1][c.first] == -1 && !m_fields[c.second - 1][c.first])
//		{
//			Q[c.second - 1][c.first] = Q[c.second][c.first] + 1;
//			queue << Cell(c.first, c.second - 1);
//			P[Cell(c.first, c.second - 1)] = c;
//		}
//		if(c.second < Lines::CellsNumber - 1 && Q[c.second + 1][c.first] == -1 && !m_fields[c.second + 1][c.first])
//		{
//			Q[c.second + 1][c.first] = Q[c.second][c.first] + 1;
//			queue << Cell(c.first, c.second + 1);
//			P[Cell(c.first, c.second + 1)] = c;
//		}
//	}
//	//if(Q[to.second][to.first] == -1)
//	/*for(int y = 0; y < Lines::CellsNumber; y++)
//	{
//		for(int x = 0; x < Lines::CellsNumber; x++)
//			qDebug("%4d", Q[y][x]);
//		//printf("\n");
//		qDebug("\n");
//	}*/
//	path.clear();
//	if(Q[to.second][to.first] == -1)
//		return false;
//	Cell c = to;
//	while(c != from)
//	{
//		path.push_front(c);
//		if(!P.contains(c))
//		{
//			qDebug() << "internal error";
//			break;
//		}
//		c = P[c];
//	}
//	path.push_front(c);
//	qDebug() << path;
//	return true;
//}

//bool Lines::Scene::findLines()
//{
//	QSet<Cell> cellsForRemove;
//	int len = 5;
//	for(int y = 0; y < Lines::CellsNumber - len + 1; y++)
//		for(int x = 0; x < Lines::CellsNumber; x++)
//		{
//			if(!m_fields[y][x])
//				continue;
//			bool f = true;
//			Lines::Ball::Color c = m_fields[y][x]->color();
//			for(int i = 1; i < len; i++)
//				if(!m_fields[y + i][x] || m_fields[y + i][x] && m_fields[y + i][x]->color() != c)
//				{
//					f = false;
//					break;
//				}
//			if(f)
//				for(int i = 0; i < len; i++)
//					cellsForRemove << Cell(x, y + i);
//			//qDebug() << "line! " << x << "  " << y;
//		}
//	for(int y = 0; y < Lines::CellsNumber; y++)
//		for(int x = 0; x < Lines::CellsNumber - len + 1; x++)
//		{
//			if(!m_fields[y][x])
//				continue;
//			bool f = true;
//			Lines::Ball::Color c = m_fields[y][x]->color();
//			for(int i = 1; i < len; i++)
//				if(!m_fields[y][x + i] || m_fields[y][x + i] && m_fields[y][x + i]->color() != c)
//				{
//					f = false;
//					break;
//				}
//			if(f)
//				for(int i = 0; i < len; i++)
//					cellsForRemove << Cell(x + i, y);
//			//qDebug() << "line! " << x << "  " << y;
//		}
//	for(int y = 0; y < Lines::CellsNumber - len + 1; y++)
//		for(int x = 0; x < Lines::CellsNumber - len + 1; x++)
//		{
//			if(!m_fields[y][x])
//				continue;
//			bool f = true;
//			Lines::Ball::Color c = m_fields[y][x]->color();
//			for(int i = 1; i < len; i++)
//				if(!m_fields[y + i][x + i] || m_fields[y + i][x + i] && m_fields[y + i][x + i]->color() != c)
//				{
//					f = false;
//					break;
//				}
//			if(f)
//				for(int i = 0; i < len; i++)
//					cellsForRemove << Cell(x + i, y + i);
//			//qDebug() << "line! " << x << "  " << y;
//		}
//	for(int y = 0; y < Lines::CellsNumber - len + 1; y++)
//		for(int x = len - 1; x < Lines::CellsNumber; x++)
//		{
//			if(!m_fields[y][x])
//				continue;
//			bool f = true;
//			Lines::Ball::Color c = m_fields[y][x]->color();
//			for(int i = 1; i < len; i++)
//				if(!m_fields[y + i][x - i] || m_fields[y + i][x - i] && m_fields[y + i][x - i]->color() != c)
//				{
//					f = false;
//					break;
//				}
//			if(f)
//				for(int i = 0; i < len; i++)
//					cellsForRemove << Cell(x - i, y + i);
//			//qDebug() << "line! " << x << "  " << y;
//		}
//	//qDebug() << cellsForRemove;
//	if(cellsForRemove.isEmpty())
//		return false;
//	m_sound->play();
//	int b = cellsForRemove.count();
//	foreach(const Cell &c, cellsForRemove)
//	{
//		Lines::Ball *ball = m_fields[c.second][c.first];
//		m_fields[c.second][c.first] = 0;
//		delete ball;
//	}
//	m_score += 2 * b * b - 20 * b + 60;
//	m_infoPanel->setScore(m_score);

//	qDebug() << m_score;
//	return true;
//}*/
