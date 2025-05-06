#include <QLinearGradient>
#include <QPen>
#include "paddle.h"

const QSize Paddle::PADDLE_SIZE(100, 15);

Paddle::Paddle(QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    setRect(0, 0, PADDLE_SIZE.width(), PADDLE_SIZE.height());

    QLinearGradient linearGrad(QPoint(0, 0), QPoint(PADDLE_SIZE.width(), PADDLE_SIZE.height()));
    linearGrad.setColorAt(0, QRgb(0xDCDCDC));
    linearGrad.setColorAt(1, QRgb(0xA9A9A9));

    setPen(QPen(Qt::NoPen));
    setBrush(linearGrad);
}

double Paddle::getCenterX()
{
    return x() + rect().width() / 2;
}

void Paddle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    double mouseX = (mapToScene(event->pos())).x();
    setPos(mouseX - rect().width() / 2, y());
}
