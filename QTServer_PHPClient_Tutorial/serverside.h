#ifndef SERVERSIDE_H
#define SERVERSIDE_H

#include <QObject>

#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <QList>

class ServerSide : public QObject
{
    Q_OBJECT
public:
    //explicit ServerSide(QObject *parent = nullptr);  <-- this line can be deleted because we will make our own constructor without a default null pointer

    ServerSide(QObject *pwgt);  /* <-- Our custom constructor */

    QTcpServer *tcpServer;  /* <-- We create a instance of tcpServer */
    QList<QTcpSocket *> getClients(); /* <-- getter function to get clients list */

public slots:

    virtual void newConnection();  /* <-- SLOT for new connection */
    void readClient();  /* <-- SLOT for reading client message */
    void gotDisconnection(); /* <-- SLOT that will get called when somebody discconects */
    qint64 sendToClient(QTcpSocket *socket, const QString &str); /* <-- SLOT to send message to client (clientSocket, message) */

signals:

    void gotNewMessage(QString msg); /* <-- SIGNAL that gets triggered when we get a new message */
    void smbDisconnected(); /* <-- Signal that gets triggered when somebody discconects */

private:

    QList<QTcpSocket *> clients;  /* <-- a QTcpSocket list where we will store our connected clients (sockets) */

};

#endif // SERVERSIDE_H
