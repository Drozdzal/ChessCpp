#ifndef LANSERVER_H
#define LANSERVER_H


#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include "MultiThread.h"

class MyServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = 0);
    void startServer();
    QTcpSocket* player1=nullptr;
    QTcpSocket* player2=nullptr;
    std::list<QTcpSocket *> clients;
    void playersConnected();

signals:


public slots:
    void newClient();
    void receivedMsg();

protected:

};

#endif // LANCLIENT_H
