#ifndef PADDLE_H
#define PADDLE_H

#include <QGraphicsRectItem>
#include <QLinearGradient>
#include <QPen>
#include <QGraphicsSceneMouseEvent>

class Paddle: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Paddle(QGraphicsItem* parent = NULL);
    double getCenterX();

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent*) override;
};

#endif // PADDLE_H
