#include "ball.h"
#include <QRadialGradient>
#include <QTimer>
#include "paddle.h"
#include "block.h"
#include "game.h"

const int Ball::BALL_DIAMETER = 30;
const int Ball::FPS = 15;
const int Ball::COLLISION_TRESHHOLD = 15;
const int Ball::INFLU_FACTOR = 15; // minél kisebb, annál élesebben/gyorsabban reagál a változásokra a golyó

Ball::Ball(QGraphicsItem *parent) : QGraphicsEllipseItem(parent)
{
	setRect(0, 0, BALL_DIAMETER, BALL_DIAMETER);
	QRadialGradient radGrad(QPoint(BALL_DIAMETER / 2 + 10, BALL_DIAMETER / 2 + 10), BALL_DIAMETER / 2 + 10);
	radGrad.setColorAt(0, QRgb(0x9c0412)); // sötét vörös
	radGrad.setColorAt(1, QRgb(0xfc3468)); // világos piros
	setBrush(radGrad);

	xDirection = 0;
	yDirection = -5; // felfelé mozdul a golyó

	timer = new QTimer();
	connect(timer, &QTimer::timeout, this, &Ball::move);
	timer->start(FPS);
}

void Ball::move()
{
	reverseDirectionIfOutOfBounds();
	handlePaddleCollision();
	handleBlockCollision();

	moveBy(xDirection, yDirection);
}

double Ball::getCenterX()
{
	return x() + rect().width() / 2;
}

void Ball::reverseDirectionIfOutOfBounds()
{
	double appWidth = Game::WINDOW_SIZE.width();
	int loseHeight = Game::WINDOW_SIZE.height();

	// bal oldal
	if ((mapToScene(rect().topLeft())).x() <= 0)
	{
		xDirection = -1 * xDirection; // megfordítjuk az x irányt, mivel sokat használjuk, ezért lehetne ez külön függvény is
	}

	// jobb oldal
	else if ((mapToScene(rect().topRight())).x() >= appWidth)
	{
		xDirection = -1 * xDirection;
	}

	// fenti oldal
	else if ((mapToScene(rect().topLeft())).y() <= 0)
	{
		yDirection = -1 * yDirection;
	}

	// lenti oldal
	else if ((mapToScene(rect().bottomRight())).y() > loseHeight)
	{
		// a golyó közepe eléri a képernyő aljáról (kiesett)
		timer->disconnect(this);
		timer->stop();
		emit defeat();
	}
}
void Ball::handlePaddleCollision()
{
	QList<QGraphicsItem *> collidedItems = collidingItems();

	for (QGraphicsItem *item : collidedItems)
	{
		Paddle *paddle = dynamic_cast<Paddle *>(item);

		if (paddle)
		{
			yDirection = -1 * yDirection;

			double ballCenterX = getCenterX();
			double paddleCenterX = paddle->getCenterX();
			double delta = ballCenterX - paddleCenterX;

			xDirection = (xDirection + delta) / INFLU_FACTOR;

			return; // csak egy ütközés / frame érdekel minket
		}
	}
}
void Ball::handleBlockCollision()
{
	QList<QGraphicsItem *> collidedItems = collidingItems();
	for (QGraphicsItem *item : collidedItems)
	{
		Block *block = dynamic_cast<Block *>(item);

		if (block)
		{
			QPointF ballPos = pos();
			QPointF blockPos = block->pos();
			// avagy:
			// double blockX = block->pos().x();
			// double blockY = block->pos().y();

			if (ballPos.y() > blockPos.y() + COLLISION_TRESHHOLD)
			{
				yDirection *= -1;
			}

			else if (ballPos.x() >= blockPos.x() + COLLISION_TRESHHOLD)
			{
				xDirection *= -1;
			}

			emit blockRemoved(block);
			return;
		}
	}
}
