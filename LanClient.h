#ifndef LANCLIENT_H
#define LANCLIENT_H


#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QThreadPool>


class MyClient : public QObject
{
    Q_OBJECT
public:
    explicit MyClient(QObject *parent = 0);
    void connectToServer();
    void sendMessage();
//signals:

//public slots:
//    void connected();
//    void disconnected();
//    void readyRead();

//    // make the server fully ascynchronous
//    // by doing time consuming task
//    void TaskResult(int Number);

private:
    QTcpSocket *socket;

};

#endif // LANCLIENT_H
