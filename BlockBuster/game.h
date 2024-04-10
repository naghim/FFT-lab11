#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "paddle.h"
#include "block.h"

class Game : public QGraphicsView
{
    Q_OBJECT

public:
    Game(QWidget *parent = nullptr);
    ~Game();

    void start();
    void victory();
    void lost();

    void generateBlockGrid();
    void generateBlockCol(double);

    QGraphicsScene* scene;
    int numberOfBlocks = 7*5;
    int numOfCols = 7;
    int numOfRows = 5;
    int heightOfBlocks = 25;
    int widthOfBlocks = 50;
};
#endif // GAME_H
