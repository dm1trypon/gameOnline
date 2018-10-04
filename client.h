#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QTcpSocket>

class Client : public QWidget
{
    Q_OBJECT
public:
    Client(const QString& strHost ,int nPort, QWidget *parent = nullptr);
private:
    QString _strHost;
    int _nPort;
    const QString TYPE = "type";
    const QString CONNECTION = "connection";
    const QString MOVE = "move";
    const QString NICKNAME = "nickName";
    const QString SPEEDX = "speedX";
    const QString SPEEDY = "speedY";
    const QString POSX = "posX";
    const QString POSY = "posY";
    QTcpSocket* m_pTcpSocket;
    quint16 m_nNextBlockSize;
    QString addToJsonOnMove(int speedX, int speedY);
    QString addToJsonOnConnected(int posX, int posY);
    QString _nickName;
private slots:
    void slotReadyRead();
    void slotError(QAbstractSocket::SocketError err);
    void slotConnected();
    void slotSendPositionToServer(int speedX, int speedY);
    void slotOnConnectedPlayer(qreal posX, qreal posY);
    void slotSetNickName(QString nickName);
signals:
    void signalConnectedToServer();
};

#endif // CLIENT_H
