#include "linksignal.h"


LinkSignal &LinkSignal::Instance()
{
    static LinkSignal theSingleInstance;
    return theSingleInstance;
}

void LinkSignal::connectedToServer()
{
    emit signalConnectedToServer();
}

void LinkSignal::positionPlayer(qreal setX, qreal setY)
{
    emit signalPositionPlayer(setX, setY);
}

void LinkSignal::movePlayer(int xSpeed, int ySpeed)
{
    emit signalMovePlayer(xSpeed, ySpeed);
}

void LinkSignal::createEnemyPlayer(qreal posX, qreal posY)
{
    emit signalCreateEnemyPlayer(posX, posY);
}

void LinkSignal::moveEnemyPlayer(int speedX, int speedY)
{
    emit signalMoveEnemyPlayer(speedX, speedY);
}
