#include "enemyplayer.h"
#include "linksignal.h"


EnemyPlayer::EnemyPlayer(qreal posX, qreal posY) : QObject(), QGraphicsPixmapItem (nullptr)
{
    setPixmap(QPixmap(":/img/enemy_player.png"));
    setPos(posX, posY);
    connect(&LinkSignal::Instance(), SIGNAL(signalMoveEnemyPlayer(int, int)), SLOT(onMoveEvent(int, int)));
}

void EnemyPlayer::advance(int phase)
{
    if (phase <= 0) {
        collisionObjects();
    }
    if (phase >= 1) {
        movePlayer();
    }
//    if (collision()) {
//        endGameMessageSpaceship(ENDGAME);
//        delete this;
//    }
}

int EnemyPlayer::type() const
{
    return Type;
}

void EnemyPlayer::movePlayer()
{
    moveBy(xSpeed, ySpeed);
    setRotation(xSpeed);
}
void EnemyPlayer::collisionObjects()
{

}

void EnemyPlayer::onMoveEvent(int speedX, int speedY)
{
    xSpeed = speedX;
    ySpeed = speedY;
}
