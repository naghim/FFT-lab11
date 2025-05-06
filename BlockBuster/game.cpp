#include "game.h"
#include "ball.h"
#include "paddle.h"
#include "block.h"

const int Game::NUM_BLOCKS = 35;
const int Game::NUM_COLS = 7;
const int Game::NUM_ROWS = 5;
const QSize Game::WINDOW_SIZE(370, 600);
const QSize Game::INITIAL_BALL_POS(200, 500);
const QSize Game::INITIAL_PADDLE_POS(150, 575);
const int Game::BLOCK_SPACING = 3;

Game::Game(QWidget *parent)
	: QGraphicsView(parent)
{
	scene = new QGraphicsScene(0, 0, WINDOW_SIZE.width(), WINDOW_SIZE.height());
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setFixedSize(WINDOW_SIZE.width(), WINDOW_SIZE.height());

	setScene(scene);
	setMouseTracking(true);
}

Game::~Game() {}

void Game::start()
{
	// golyó
	ball = new Ball();
	ball->setPos(INITIAL_BALL_POS.width(), INITIAL_BALL_POS.height());
	scene->addItem(ball);

	// csúszka
	paddle = new Paddle;
	paddle->setPos(INITIAL_PADDLE_POS.width(), INITIAL_PADDLE_POS.height());
	scene->addItem(paddle);
	paddle->grabMouse();

	// téglák
	generateBlockGrid();

	connect(ball, &Ball::victory, this, &Game::onVictory);
	connect(ball, &Ball::defeat, this, &Game::onDefeat);
	connect(ball, &Ball::blockRemoved, this, &Game::onBlockRemoved);
}

void Game::onVictory()
{
	qDebug() << "Victory";
	// TODO
}

void Game::onDefeat()
{
	qDebug() << "Game over";
	// ha nem működik a qDebug, akkor: fprintf(stderr, "%s\n", "Game over");
	// TODO
}

void Game::generateBlockGrid()
{
	for (int i = 0; i < NUM_COLS; i++)
	{
		// oszlop száma * (block mérete + köztök lévő hely)
		generateBlockCol(i * (Block::BLOCK_SIZE.width() + BLOCK_SPACING));
	}
}

void Game::generateBlockCol(int x)
{
	for (int i = 0; i < NUM_ROWS; i++)
	{
		Block *block = new Block();
		// hanyadik oszlop, hanyadik az oszlopban * (blocknak a magassága + a hézag mérete)
		block->setPos(x, i * (Block::BLOCK_SIZE.height() + BLOCK_SPACING));
		scene->addItem(block);
	}
}

int Game::remainingBlocks()
{
	// TODO

	return 43;
}

void Game::onBlockRemoved(Block *block)
{
	scene->removeItem(block);
	delete block;

	if (remainingBlocks() == 0)
	{
		// Nincs több blokk, győzelem
		onVictory();
	}
}
