#include "LanServer.h"

MyServer::MyServer(QObject *parent) :
    QTcpServer(parent)
{

    connect(this, &QTcpServer::newConnection, this,&MyServer::newClient);
    connect(player1, &QTcpSocket::readyRead, this,&MyServer::receivedMsg);

}

void MyServer::newClient()
{
    qDebug()<<"Added new client";
    player1=this->nextPendingConnection();
    clients.push_back(this->nextPendingConnection());
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

void MyServer::receivedMsg()
{
    QByteArray data = player1->readAll();
    qDebug()<<"Received" << data << "\n";
}

