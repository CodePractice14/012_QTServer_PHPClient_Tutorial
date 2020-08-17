#include "serverside.h"

ServerSide::ServerSide(QObject *pwgt) : QObject(pwgt)
{
    tcpServer = new QTcpServer(this); /* <-- Create a new instance of the tcpServer and store it in our tcpServer field */
}

QList<QTcpSocket *> ServerSide::getClients()
{
    return clients;
}

void ServerSide::newConnection()
{
    /* (1) Create a new pointer and store the connection */
    QTcpSocket *clientSocket = tcpServer->nextPendingConnection();

    /* (2) Connects the clientConnection to special QTcpSocket signal / slot
     * My understanding: when this clientSocket gets discconected --> it will be send to delete list*/
    connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
    /* (3) Connects the clientConnection to our custom signal / slot
     * My understanding: when this clientSocket gets new data --> we call our readClient function */
    connect(clientSocket, &QTcpSocket::readyRead, this, &ServerSide::readClient);
    /* (3) Connects the clientConnection to our custom signal / slot
     * My understanding: when this clientSocket gets discconected --> we call our gotDisconnection function */
    connect(clientSocket, &QTcpSocket::disconnected, this, &ServerSide::gotDisconnection);
    /* (4) Add the current connection to our clients list*/
    clients << clientSocket;
    /* (5) We call our sendToClient function and send him a reply to let him know we successfully connected*/
    //sendToClient(clientSocket, "Reply: connection established");
}

void ServerSide::readClient()
{
    qDebug() << "New incoming transmition";

    /* (1) Convert the sender [the signal that triggers this slot],to a QTcpSocket*/
    QTcpSocket *clientSocket = (QTcpSocket*)sender();
    /* (2) Prepare a byte Array where we will store our message */
    QByteArray data;

    /* (3) Start a continuous loop ... */
    while(true)
    {
        /* (4) Read bytes from socket and add to a temporary byte array */
        QByteArray tmp = clientSocket->readAll();
        /* (5) Add the contains of our temporary array to our main array */
        data += tmp;
        /* (6) IF there are no more bits to read we break the continuous loop */
        if (tmp.isEmpty()  && !clientSocket->waitForReadyRead(500))
        {
            break;
        }
    }
    /* (7) Print q message with the data recived and its length */
    qDebug("Data recieved: %s (len = %d)", data.constData(), data.length());

    /* (8) Save the message into a string */
    QString str;
    str = QString(data.constData());

    /* (9) Emit a gotNewMessage SIGNAL with our message */
    emit gotNewMessage(str);

    /* (10) Attempt to send a message to the client that we have recived its data*/
    if(sendToClient(clientSocket, QString("Recived: [%1]").arg(str)) == -1)
    {
        /* (11) IF it fails for any reason we log a message*/
        qDebug() << "Some error occured";
    }
}

qint64 ServerSide::sendToClient(QTcpSocket* socket, const QString &str)
{
    /* (1) Create a Byte Array to store our bytes */
    QByteArray arrBlock;
    /* (2) Convert our string to bytes array */
    arrBlock = str.toUtf8();

    return socket->write(arrBlock);
}

void ServerSide::gotDisconnection()
{
    /* (1) Remove the clientSocket that triggers this function from our list*/
    clients.removeAt(clients.indexOf((QTcpSocket*)sender()));
    /* (2) Emit a somebodyDisconnect signal*/
    emit smbDisconnected();
}
