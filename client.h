#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QTcpSocket>
#include <QJsonArray>

class Client : public QWidget
{
    Q_OBJECT
public:
    Client(const QString& strHost ,int nPort, QWidget *parent = nullptr);
private:
    const QString CLIENTS_LIST = "clientsList";
    const QString TYPE = "type";
    const QString CONNECTION = "connection";
    const QString MOVE = "move";
    const QString NICKNAME = "nickName";
    const QString POSX = "posX";
    const QString POSY = "posY";

    QString _strHost;
    int _nPort;
    QJsonArray _arrClients;
    QTcpSocket* m_pTcpSocket;
    quint16 m_nNextBlockSize;
    QString _nickName;
    bool onFind(QJsonObject jsObj);
    void processParse(QString data);
private slots:
    void slotReadyRead();
    void slotError(QAbstractSocket::SocketError err);
    void slotConnected();
    void slotPositionToJson(qreal posX, qreal posY);
    void slotConnectionToJson(qreal posX, qreal posY);
    void slotOnConnection(QString nickName);
    void slotSender(QString data);
signals:
    void signalConnectedToServer();
};

#endif // CLIENT_H
