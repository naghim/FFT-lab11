#ifndef BALL_H
#define BALL_H

#include <QGraphicsEllipseItem>
#include <QTimer>

class Block;

class Ball : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    static const int BALL_DIAMETER;
    static const int FPS;
    static const int COLLISION_TRESHHOLD;
    static const int INFLU_FACTOR;

    explicit Ball(QGraphicsItem *parent = nullptr);
    ~Ball() override = default;

    double getCenterX();
    QTimer *timer;

public slots:
    void move();

signals:
    void victory();
    void defeat();
    void blockRemoved(Block *block);

private:
    double xDirection;
    double yDirection;

    void reverseDirectionIfOutOfBounds();
    void handlePaddleCollision();
    void handleBlockCollision();
};

#endif // BALL_H
