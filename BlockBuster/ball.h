#ifndef BALL_H
#define BALL_H

#include <QGraphicsEllipseItem>
#include <QRadialGradient>
#include <QTimer>
#include "game.h"
#include "paddle.h"
#include "block.h"

extern Game *game;

class Ball: public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    Ball(QGraphicsItem* parent = NULL);
    double getCenterX();
    QTimer *timer;

    enum Finisher{
        Lost,
        Won
    };

public slots:
    void move();

private:
    double xDirection;
    double yDirection;

    void reverseDirectionIfOutOfBounds();
    void handlePaddleCollision();
    void handleBlockCollision();
    void gameFinished(Ball::Finisher condition);
};

#endif // BALL_H
