#include "linksignal.h"
#include "widget.h"


LinkSignal &LinkSignal::Instance()
{
    static LinkSignal theSingleInstance;
    return theSingleInstance;
}

void LinkSignal::connectedToServer()
{
    emit signalConnectedToServer();
}

void LinkSignal::positionPlayer(qreal posX, qreal posY)
{
    emit signalPositionPlayer(posX, posY);
}

void LinkSignal::movePlayer(qreal posX, qreal posY)
{
    emit signalMovePlayer(posX, posY);
}

void LinkSignal::createEnemyPlayer(qreal posX, qreal posY)
{
    emit signalCreateEnemyPlayer(posX, posY);
}

void LinkSignal::getNickName(QString nickName)
{
    emit signalGetNickName(nickName);
}

void LinkSignal::moveEnemyPlayer(qreal posX, qreal posY)
{
    emit signalMoveEnemyPlayer(posX, posY);
}

bool LinkSignal::onFrameBoard(qreal posX, qreal posY)
{
    return posX < SCENE_WIDTH && posX > 0 && posY < SCENE_HEIGHT && posY > 0;
}

void LinkSignal::workWithJson(QString data)
{
    emit signalWorkWithJson(data);
}

void LinkSignal::jsonOnMove(qreal posX, qreal posY, QString type)
{
    emit signalJsonOnMove(posX, posY, type);
}

void LinkSignal::jsonOnConnection(qreal posX, qreal posY, QString type)
{
    emit signalJsonOnConnection(posX, posY, type);
}

void LinkSignal::compactJson(QString strJson)
{
    emit signalCompactJson(strJson);
}
