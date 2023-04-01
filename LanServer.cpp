#include "LanServer.h"

MyServer::MyServer(QObject *parent) :
    QTcpServer(parent)
{

    connect(this, &QTcpServer::newConnection, this,&MyServer::newClient);

}

void MyServer::newClient()
{
    qDebug()<<"Added new client";
    if (player1==nullptr)
    {
    player1=this->nextPendingConnection();
    connect(player1, &QTcpSocket::readyRead, this,&MyServer::receivedPlayer1Msg);

    }
    else if (player2==nullptr)
    {
        player2=this->nextPendingConnection();
        connect(player2, &QTcpSocket::readyRead, this,&MyServer::receivedPlayer2Msg);

    }
}

void MyServer::startServer()
{
    if(!this->listen(QHostAddress::Any,1234))
    {
        qDebug() << "Could not start server";
    }
    else
    {
        qDebug() << "Listening...";
    }
}

void MyServer::playersConnected()
{
}

void MyServer::receivedPlayer1Msg()
{
    QByteArray data = player1->readAll();
    qDebug()<<"Received Player1msg" << data << "\n";
    if (player2!=nullptr)
    {
    player2->write(data);
    }
}

void MyServer::receivedPlayer2Msg()
{
    QByteArray data = player2->readAll();
    qDebug()<<"Received Player2msg" << data << "\n";
    if (player1!=nullptr)
    {
    player1->write(data);
    }
}

