#include "block.h"
#include <QLinearGradient>
#include <QPen>

const QSize Block::BLOCK_SIZE(50, 25);

Block::Block(QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    setRect(0, 0, BLOCK_SIZE.width(), BLOCK_SIZE.height());

    QLinearGradient linearGrad(QPoint(0, 0), QPoint(BLOCK_SIZE.width(), BLOCK_SIZE.width()));
    linearGrad.setColorAt(0, QRgb(0xfa4988));
    linearGrad.setColorAt(1, QRgb(0x728ef0));

    setPen(QPen(Qt::NoPen));
    setBrush(linearGrad);
}
