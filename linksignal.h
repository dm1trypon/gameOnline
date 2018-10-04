#ifndef LINKSIGNAL_H
#define LINKSIGNAL_H


#include <QWidget>

class LinkSignal : public QObject {
    Q_OBJECT

private:
    LinkSignal(){}
    LinkSignal(const LinkSignal& root) = delete;
    LinkSignal& operator=(const LinkSignal&) = delete;
public:
    void connectedToServer();
    void positionPlayer(qreal setX, qreal setY);
    void movePlayer(int xSpeed, int ySpeed);
    void createEnemyPlayer(qreal posX, qreal posY);
    void moveEnemyPlayer(int speedX, int speedY);
    static LinkSignal& Instance();
    void getNickName(QString nickName);
signals:
    void signalConnectedToServer();
    void signalPositionPlayer(qreal setX, qreal setY);
    void signalMovePlayer(int xSpeed, int ySpeed);
    void signalCreateEnemyPlayer(qreal posX, qreal posY);
    void signalMoveEnemyPlayer(int speedX, int speedY);
    void signalGetNickName(QString nickName);
};
#endif // LINKSIGNAL_H
