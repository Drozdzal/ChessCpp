#include <QApplication>
#include "Game.h"
#include "Loader.h"
Game* game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    game = new Game();
    game->start();
    Loader loader = Loader();
    loader.readJson(QString("D:/mgr/cpp/Chess/rozgrywki/rozgrywka.json"));
    game->show();
    loader.firstMoveFromJson();
//    game->show();
//    game->displayStart();

    return a.exec();
}
