#include "game.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Game *game = new Game();
    game->show();
    game->setWindowTitle("BlockBuster");
    game->start();

    return a.exec();
}
