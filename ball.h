#ifndef BALL_H
#define BALL_H

#include <QObject>
#include <QGraphicsPixmapItem>

#include "globals.h"
class QTimeLine;

namespace Lines
{

class Ball : public QObject, public QGraphicsPixmapItem
{
	Q_OBJECT
public:
	enum Color {None, Blue, Green, Orange, Red, Purple, Yellow, White};
	explicit Ball(Color color);
	virtual ~Ball() {}

	Cell cell() const;
	int fieldX() const {return m_fieldX; }
	int fieldY() const {return m_fieldY; }
	void setField(int x, int y);

	Color color() const {return m_color; }
	void setColor(Color color);
	void setFrame(int f);
	void setBirthFrame(int f);
	void setMoveFrame(int f);
	void setXplodeFrame(int f);

	void select();
	void deselect();

	static Color randomColor();

private slots:
	void updateFrame(int f);
//signals:
//	void selected();

protected:
	//void mousePressEvent(QGraphicsSceneMouseEvent *event);
	//void mouseReleaseEvent(QGraphicsSceneMouseEvent *);

private:
	Color m_color;
	int m_fieldX;
	int m_fieldY;
	QTimeLine *m_selectTimeLine;
};

};

#endif // BALL_H
