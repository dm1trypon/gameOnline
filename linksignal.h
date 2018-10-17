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
    static LinkSignal& Instance();
    void connectedToServer();
    void positionPlayer(qreal posX, qreal posY);
    void movePlayer(qreal posX, qreal posY);
    void createEnemyPlayer(qreal posX, qreal posY);
    void moveEnemyPlayer(qreal posX, qreal posY);
    void getNickName(QString nickName);
    bool onFrameBoard(qreal posX, qreal posY);
    void workWithJson(QString data);
    void jsonOnConnection(qreal posX, qreal posY, QString type);
    void jsonOnMove(qreal posX, qreal posY, QString type);
    void compactJson(QString strJson);
signals:
    void signalConnectedToServer();
    void signalJsonOnMove(qreal posX, qreal posY, QString type);
    void signalJsonOnConnection(qreal posX, qreal posY, QString type);
    void signalPositionPlayer(qreal posX, qreal posY);
    void signalMovePlayer(qreal posX, qreal posY);
    void signalCreateEnemyPlayer(qreal posX, qreal posY);
    void signalMoveEnemyPlayer(qreal posX, qreal posY);
    void signalGetNickName(QString nickName);
    void signalWorkWithJson(QString data);
    void signalCompactJson(QString strJson);
};
#endif // LINKSIGNAL_H
