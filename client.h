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
    QTcpSocket* m_pTcpSocket;
    quint16 m_nNextBlockSize;
    QString addToJsonOnMove(int speedX, int speedY);
    QString addToJsonOnConnected(int posX, int posY);
private slots:
    void slotReadyRead();
    void slotError(QAbstractSocket::SocketError err);
    void slotConnected();
    void slotSendPositionToServer(int speedX, int speedY);
    void slotOnConnectedPlayer(qreal posX, qreal posY);
signals:
    void signalConnectedToServer();
};

#endif // CLIENT_H
