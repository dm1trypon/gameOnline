#include "client.h"
#include "linksignal.h"

#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>

Client::Client(const QString &strHost, int nPort, QWidget *parent) : QWidget (parent), m_nNextBlockSize(0)
{
    _strHost = strHost;
    _nPort = nPort;
    connect(&LinkSignal::Instance(), SIGNAL(signalMovePlayer(int, int)), SLOT(slotSendPositionToServer(int, int)));
    connect(&LinkSignal::Instance(), SIGNAL(signalPositionPlayer(qreal, qreal)), SLOT(slotOnConnectedPlayer(qreal, qreal)));
    connect(&LinkSignal::Instance(), SIGNAL(signalGetNickName(QString)), SLOT(slotSetNickName(QString)));
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
    if (jsObj.value(TYPE) == CLIENTS_LIST)
    {
        bool find = false;
        QJsonObject objClients;
        QJsonArray arrClients = jsObj[CLIENTS_LIST].toArray();
        foreach (const QJsonValue & value, arrClients)
        {
            QJsonObject objArr = value.toObject();
            foreach (const QJsonValue & _value, _arrClients)
            {
                QJsonObject _objArr = _value.toObject();
                if (objArr.value(NICKNAME) == _objArr.value(NICKNAME))
                {
                    find = true;
                    break;
                }
            }
            if ((!find) && (_nickName != objArr.value(NICKNAME).toString()))
            {
                _arrClients.push_back(objArr);
                LinkSignal::Instance().createEnemyPlayer(static_cast<qreal>(objArr.value(POSX).toString().toInt()), static_cast<qreal>(objArr.value(POSY).toString().toInt()));
                find = false;
            }
        }
    }
    if ((jsObj.value(TYPE) == MOVE) && (jsObj.value(NICKNAME) != _nickName))
    {
        LinkSignal::Instance().moveEnemyPlayer(jsObj.value(SPEEDX).toString().toInt(), jsObj.value(SPEEDY).toString().toInt());
    }
}

void Client::slotSetNickName(QString nickName)
{
    _nickName = nickName;
    m_pTcpSocket = new QTcpSocket(this);
    m_pTcpSocket->connectToHost(_strHost, static_cast<quint16>(_nPort));
    connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
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
    qDebug() << "CONNECT!";
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
    root.insert(TYPE, MOVE);
    root.insert(NICKNAME, _nickName);
    root.insert(SPEEDX, QString::number(speedX));
    root.insert(SPEEDY, QString::number(speedY));
    document.setObject(root);
    QString strJson(document.toJson(QJsonDocument::Compact));
    return strJson;
}

QString Client::addToJsonOnConnected(int posX, int posY)
{
    QJsonDocument document;
    QJsonObject root = document.object();
    root.insert(TYPE, CONNECTION);
    root.insert(NICKNAME, _nickName);
    root.insert(POSX, QString::number(posX));
    root.insert(POSY, QString::number(posY));
    document.setObject(root);
    QString strJson(document.toJson(QJsonDocument::Compact));
    return strJson;
}
