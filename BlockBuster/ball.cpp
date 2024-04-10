#include "ball.h"


Ball::Ball(QGraphicsItem *parent): QGraphicsEllipseItem(parent)
{
    setRect(0, 0, 30, 30);
    QRadialGradient radGrad(QPoint(25,25), 25);
    radGrad.setColorAt(0, QRgb(0x9c0412));
    radGrad.setColorAt(1, QRgb(0xfc3468));

    //setPen(QPen(Qt::NoPen));
    setBrush(radGrad);

    xDirection = 0;
    yDirection = -5;

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Ball::move);
    timer->start(15);
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
    return x() + rect().width()/2;
}

void Ball::reverseDirectionIfOutOfBounds()
{
    double appWidth = game->width();

    //bal oldal
    if ( (mapToScene(rect().topLeft())).x() <= 0 )
    {
        xDirection = -1 * xDirection;
    }

    //jobb oldal
    if ( (mapToScene(rect().topRight())).x() >= appWidth )
    {
        xDirection = -1 * xDirection;
    }

    //fenti oldal
    if ( (mapToScene(rect().topLeft())).y() <= 0 )
    {
        yDirection = -1 * yDirection;
    }

    //lenti oldal
    if ( (mapToScene(rect().bottomRight())).y() > 650 )
    {
        gameFinished(Ball::Lost);
    }
}
void Ball::handlePaddleCollision()
{
    QList<QGraphicsItem*> collidedItems = collidingItems();
    int n = collidedItems.size();
    for(int i=0; i<n; i++){
        Paddle* paddle = dynamic_cast<Paddle*>(collidedItems[i]);
        if (paddle){
            yDirection = -1 * yDirection;
            double ballX = getCenterX();
            double paddleX = paddle->getCenterX();

            double delta = ballX - paddleX;
            xDirection = (xDirection + delta)/15;

            return;
        }
    }
}
void Ball::handleBlockCollision()
{
    QList<QGraphicsItem*> collidedItems = collidingItems();
    int n = collidedItems.size();
    for(int i=0; i<n; i++){
        Block* block = dynamic_cast<Block*>(collidedItems[i]);
        if (block){
            double ballX = pos().x();
            double ballY = pos().y();
            double blockX = block->pos().x();
            double blockY = block->pos().y();

            if(ballY > blockY + 15)
            {
                yDirection *= -1;
            }

            if(ballX > blockX + 15)
            {
                xDirection *= -1;
            }

            game->scene->removeItem(block);
            delete block;
            // ha nincs tobb tegla, nyert

            return;
        }
    }
}

void Ball::gameFinished(Ball::Finisher condition)
{
    disconnect(timer, &QTimer::timeout, this, &Ball::move);
    if (condition == Ball::Won) {
        game->victory();
        return;
    }
    if (condition == Ball::Lost) game->lost();
}
