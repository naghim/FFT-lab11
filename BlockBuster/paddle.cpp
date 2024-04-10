#include "paddle.h"

Paddle::Paddle(QGraphicsItem* parent): QGraphicsRectItem(parent)
{
    setRect(0,0,100, 15);

    QLinearGradient linearGrad(QPoint(0,0), QPoint(100, 15));
    linearGrad.setColorAt(0, QRgb(0xDCDCDC));
    linearGrad.setColorAt(1, QRgb(0xA9A9A9));

    setPen(QPen(Qt::NoPen));
    setBrush(linearGrad);
}

double Paddle::getCenterX()
{
    return x() + rect().width()/2;
}

void Paddle::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    double mouseX = (mapToScene(event->pos())).x();
    setPos(mouseX - rect().width()/2, y());

}
