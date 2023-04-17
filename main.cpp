#include <QApplication>
#include "Game.h"
#include "Loader.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Game* game = new Game();
    game->show();


    return a.exec();
}
