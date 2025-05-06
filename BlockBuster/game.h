#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QSize>

class QGraphicsScene;
class Ball;
class Paddle;
class Block;

class Game : public QGraphicsView
{
	Q_OBJECT

public:
	static const int NUM_BLOCKS;
	static const int NUM_COLS;
	static const int NUM_ROWS;
	static const QSize WINDOW_SIZE;
	static const QSize INITIAL_BALL_POS;
	static const QSize INITIAL_PADDLE_POS;
	static const int BLOCK_SPACING;

	QGraphicsScene *scene;

	Game(QWidget *parent = nullptr);
	~Game();

	void start();

	void generateBlockGrid();
	void generateBlockCol(int);
	int remainingBlocks();

	void removeBlock(Block *block);

public slots:
	void onVictory();
	void onDefeat();
	void onBlockRemoved(Block *block);

private:
	Ball *ball;
	Paddle *paddle;
};

#endif // GAME_H
