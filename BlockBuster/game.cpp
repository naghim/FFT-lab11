#include "game.h"
#include "ball.h"

Game::Game(QWidget *parent)
    : QGraphicsView(parent)
{
    scene = new QGraphicsScene(0,0,370,600);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(370, 600);

    setScene(scene);
    setMouseTracking(true);
}

Game::~Game(){}

void Game::start()
{
    //golyo
    Ball* ball = new Ball();
    ball->setPos(200, 500);
    scene->addItem(ball);

    //csuszka
    Paddle* paddle = new Paddle();
    paddle->setPos(150, 575);
    scene->addItem(paddle);
    paddle->grabMouse();

    //teglak
    generateBlockGrid();
}

void Game::victory()
{
    qDebug() << "Victory";
}

void Game::lost()
{
    qDebug() << "Game over";
}

void Game::generateBlockGrid()
{
    for(int i=0; i< numOfCols;i++)
    {
        //oszlop szama * (block merete + koztuk levo hely)
        generateBlockCol(i*(widthOfBlocks+3));
    }
}

void Game::generateBlockCol(double x)
{
    for(int i=0; i< numOfRows; i++)
    {
        Block *block = new Block();
        //hanyadik oszlop, hanyadik az oszlopban*(blocknak a magassaga + a hezag merete)
        block->setPos(x, i*(heightOfBlocks+3));
        scene->addItem(block);
    }
}
