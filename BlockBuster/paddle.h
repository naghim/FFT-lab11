#ifndef PADDLE_H
#define PADDLE_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class Paddle : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    static const QSize PADDLE_SIZE;

    Paddle(QGraphicsItem *parent = nullptr);
    double getCenterX();

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *) override;
};

#endif // PADDLE_H
