#include <QApplication>
#include "Game.h"
#include "Loader.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Game* game = new Game();
    game->show();
//    QTcpSocket socket;
//        socket.connectToHost("localhost", 1234);
//        if (!socket.waitForConnected(3000)) {
//            qDebug() << "Could not connect to server!";
//            return 1;
//        } else {
//            qDebug() << "Connected to server!";
//        }

//        socket.waitForReadyRead(3000);
//        QByteArray response = socket.readAll();
//        qDebug() << "Server says:" << response;

//        socket.disconnectFromHost();
//    game->start();
//    Loader loader = Loader();
//    loader.readJson(QString("D:/mgr/cpp/Chess/rozgrywki/rozgrywka.json"));
//    loader.firstMoveFromJson();

    return a.exec();
}
