#include "enemyplayer.h"
#include "linksignal.h"

#include <QDebug>

EnemyPlayer::EnemyPlayer(qreal posX, qreal posY) : QObject(), QGraphicsPixmapItem (nullptr)
{
    setPixmap(QPixmap(PATH_TO_ENEMYPLAYER_IMG));
    _posX = posX;
    _posY = posY;
    setPos(posX, posY);
    qDebug() << "Enemy player has been created (" << _posX << ";" << _posY << ")";
    connect(&LinkSignal::Instance(), &LinkSignal::signalMoveEnemyPlayer, this, &EnemyPlayer::slotOnMoveEvent);
}

void EnemyPlayer::advance(int phase)
{
    if (phase <= 0) {
        collisionObjects();
    }
    if (phase >= 1) {
        movePlayer();
    }
}

void EnemyPlayer::collisionObjects()
{

}

int EnemyPlayer::type() const
{
    return Type;
}

void EnemyPlayer::movePlayer()
{
    setPos(_posX, _posY);
    qDebug() << "Move enemy player (" << _posX << ";" << _posY << ")";
}

void EnemyPlayer::slotOnMoveEvent(int posX, int posY)
{
    _posX = posX;
    _posY = posY;
}
