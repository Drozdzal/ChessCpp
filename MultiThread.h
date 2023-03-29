#ifndef MULTITHREAD_H
#define MULTITHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>
class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(qintptr ID, QObject *parent = 0);

    QTcpSocket *socket;
    void run();
    void send(QByteArray Data);

signals:
    void error(QTcpSocket::SocketError socketerror);

public slots:
    void readyRead();
    void disconnected();

private:
    qintptr socketDescriptor;
    static std::list<MyThread*> socketList;
};

#endif // MULTITHREAD_H
