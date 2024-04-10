#include "block.h"

Block::Block(QGraphicsItem *parent): QGraphicsRectItem(parent)
{
    setRect(0, 0, 50, 25);

    QLinearGradient linearGrad(QPoint(0,0), QPoint(50, 50));
    linearGrad.setColorAt(0, QRgb(0xfa4988));
    linearGrad.setColorAt(1, QRgb(0x728ef0));

    setPen(QPen(Qt::NoPen));

    setBrush(linearGrad);
}
