#include "client.h"
#include "linksignal.h"

#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>

Client::Client(const QString &strHost, int nPort, QWidget *parent) : QWidget (parent), m_nNextBlockSize(0)
{
    m_pTcpSocket = new QTcpSocket(this);
    m_pTcpSocket->connectToHost(strHost, static_cast<quint16>(nPort));
    connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(&LinkSignal::Instance(), SIGNAL(signalMovePlayer(int, int)), SLOT(slotSendPositionToServer(int, int)));
    connect(&LinkSignal::Instance(), SIGNAL(signalPositionPlayer(qreal, qreal)), SLOT(slotOnConnectedPlayer(qreal, qreal)));
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
    qDebug() << "DATA:" << data;
    m_nNextBlockSize = 0;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject jsObj = jsonDoc.object();
    if ((jsObj.value("type") == "connection") && (jsObj.value("nickName") != "AsatiN"))
    {
        LinkSignal::Instance().createEnemyPlayer(static_cast<qreal>(jsObj.value("posX").toString().toInt()), static_cast<qreal>(jsObj.value("posY").toString().toInt()));
    }
    if ((jsObj.value("type") == "move") && (jsObj.value("nickName") != "AsatiN"))
    {
        LinkSignal::Instance().moveEnemyPlayer(jsObj.value("speedX").toString().toInt(), jsObj.value("speedY").toString().toInt());
    }
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
    qDebug() << "CONNECTED!";
    LinkSignal::Instance().connectedToServer();
}

void Client::slotOnConnectedPlayer(qreal posX, qreal posY)
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_8);
    out << quint16(0) << addToJsonOnConnected(static_cast<int>(posX), static_cast<int>(posY));
    out.device()->seek(0);
    out << quint16(static_cast<quint16>(arrBlock.size()) - sizeof(quint16));
    m_pTcpSocket->write(arrBlock);
}

void Client::slotSendPositionToServer(int speedX, int speedY)
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_8);
    out << quint16(0) << addToJsonOnMove(speedX, speedY);
    out.device()->seek(0);
    out << quint16(static_cast<quint16>(arrBlock.size()) - sizeof(quint16));
    m_pTcpSocket->write(arrBlock);
}

QString Client::addToJsonOnMove(int speedX, int speedY)
{
    QJsonDocument document;
    QJsonObject root = document.object();
    root.insert("type", "move");
    root.insert("nickName", "AsatiN");
    root.insert("speedX", QString::number(speedX));
    root.insert("speedY", QString::number(speedY));
    document.setObject(root);
    QString strJson(document.toJson(QJsonDocument::Compact));
    return strJson;
}

QString Client::addToJsonOnConnected(int posX, int posY)
{
    QJsonDocument document;
    QJsonObject root = document.object();
    root.insert("type", "connection");
    root.insert("nickName", "AsatiN");
    root.insert("posX", QString::number(posX));
    root.insert("posY", QString::number(posY));
    document.setObject(root);
    QString strJson(document.toJson(QJsonDocument::Compact));
    return strJson;
}
