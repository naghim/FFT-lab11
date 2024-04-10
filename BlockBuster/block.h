#ifndef BLOCK_H
#define BLOCK_H

#include <QGraphicsRectItem>
#include <QLinearGradient>
#include <QPen>

class Block: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Block(QGraphicsItem *parent = NULL);
};

#endif // BLOCK_H
