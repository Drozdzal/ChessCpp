#include "LanClient.h"

MyClient::MyClient(QObject *parent) :
    QObject(parent)
{
    socket=new QTcpSocket();
}

void MyClient::connectToServer()
{
    socket->connectToHost("localhost",1234);
    if (!socket->waitForConnected(3000)) {
        qDebug() << "Could not connect to server!";
    } else {
        qDebug() << "Connected to server!";
    }
    connect(socket, &QTcpSocket::readyRead, this,&MyClient::receivedServerMsg);

//    socket->waitForReadyRead(3000);
//    QByteArray response = socket->readAll();
//    qDebug() << "Server says:" << response;
}

void MyClient::sendMessage()
{
    QString message = "Hello, server!";
    socket->write(message.toUtf8());
    socket->flush();
    qDebug()<<"Client sent message";
}

void MyClient::receivedServerMsg()
        {
    QByteArray data = socket->readAll();
    qDebug()<<"Received msg from oponent" << data << "\n";
        }
