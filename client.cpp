#include "client.h"
#include "linksignal.h"
#include "parser.h"

#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>

Client::Client(const QString &strHost, int nPort, QWidget *parent) : QWidget (parent), m_nNextBlockSize(0)
{
    _strHost = strHost;
    _nPort = nPort;
    connect(&LinkSignal::Instance(), &LinkSignal::signalMovePlayer, this, &Client::slotPositionToJson);
    connect(&LinkSignal::Instance(), &LinkSignal::signalPositionPlayer, this, &Client::slotConnectionToJson);
    connect(&LinkSignal::Instance(), &LinkSignal::signalGetNickName, this, &Client::slotOnConnection);
    connect(&LinkSignal::Instance(), &LinkSignal::signalCompactJson, this, &Client::slotSender);
}

void Client::slotReadyRead()
{
    QDataStream in(m_pTcpSocket);
    in.setVersion(QDataStream::Qt_5_8);
    if (!m_nNextBlockSize)
    {
        in >> m_nNextBlockSize;
    }
    QString data;
    in >> data;
    qDebug() << "Incoming data from server:" << data;
    m_nNextBlockSize = 0;
    LinkSignal::Instance().workWithJson(data);
}

void Client::slotOnConnection(QString)
{
    m_pTcpSocket = new QTcpSocket(this);
    m_pTcpSocket->connectToHost(_strHost, static_cast<quint16>(_nPort));
    connect(m_pTcpSocket, &QTcpSocket::connected, this, &Client::slotConnected);
    connect(m_pTcpSocket, &QTcpSocket::readyRead, this, &Client::slotReadyRead);
}

void Client::slotError(QAbstractSocket::SocketError err)
{
    QString strError =
            "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                         "The host was not found." :
                         err == QAbstractSocket::RemoteHostClosedError ?
                         "The remote host is closed." :
                         err == QAbstractSocket::ConnectionRefusedError ?
                         "The connection was refused." :
                         QString(m_pTcpSocket->errorString())
                        );
    QMessageBox::critical(nullptr, "Server Error", "Unable to start the server:" + strError);
}

void Client::slotConnected()
{
    qDebug() << "Server connected!";
    LinkSignal::Instance().connectedToServer();
}

void Client::slotConnectionToJson(qreal posX, qreal posY)
{
    LinkSignal::Instance().jsonOnConnection(posX, posY, CONNECTION);
}

void Client::slotPositionToJson(qreal posX, qreal posY)
{
    LinkSignal::Instance().jsonOnMove(posX, posY, MOVE);
}

void Client::slotSender(QString data)
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_8);
    out << quint16(0) << data;
    out.device()->seek(0);
    m_pTcpSocket->write(arrBlock);
}
