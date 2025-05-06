#ifndef BLOCK_H
#define BLOCK_H

#include <QGraphicsRectItem>

class Block : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    static const QSize BLOCK_SIZE;

    explicit Block(QGraphicsItem *parent = nullptr);
};

#endif // BLOCK_H
