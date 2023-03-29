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
    socket->waitForReadyRead(3000);
    QByteArray response = socket->readAll();
    qDebug() << "Server says:" << response;
}

void MyClient::sendMessage()
{
    QString message = "Hello, server!";
    socket->write(message.toUtf8());
    socket->flush();
}
