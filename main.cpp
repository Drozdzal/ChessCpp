#include <QApplication>
#include "Game.h"

Game* game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    game = new Game();
    game->show();
    game->displayStart();
//    game->start();

    return a.exec();
}
