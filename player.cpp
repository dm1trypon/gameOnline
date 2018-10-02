#include "player.h"
#include "widget.h"
#include "linksignal.h"

Player::Player(qreal posX, qreal posY) : QObject(), QGraphicsPixmapItem (nullptr)
{
    setPixmap(QPixmap(":/img/player.png"));
    setPos(posX, posY);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
}

void Player::advance(int phase)
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

int Player::type() const
{
    return Type;
}

void Player::movePlayer()
{
    moveBy(xSpeed, ySpeed);
    setRotation(xSpeed);
}
void Player::collisionObjects()
{

}

void Player::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        xSpeed = - speedPlayer;
        LinkSignal::Instance().movePlayer(xSpeed, 0);
        break;
    case Qt::Key_Right:
        xSpeed = speedPlayer;
        LinkSignal::Instance().movePlayer(xSpeed, 0);
        break;
    case Qt::Key_Up:
        ySpeed = - speedPlayer;
        LinkSignal::Instance().movePlayer(0, ySpeed);
        break;
    case Qt::Key_Down:
        ySpeed = speedPlayer;
        LinkSignal::Instance().movePlayer(0, ySpeed);
        break;
//    case Qt::Key_Space:
//        scene()->addItem(new Bullet(mapToScene(QPointF(pixmap().width()/2, 0)), nullptr));
//        break;

    default:
        break;
    }
}

void Player::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        xSpeed = 0;
        LinkSignal::Instance().movePlayer(xSpeed, 0);
        break;
    case Qt::Key_Right:
        xSpeed = 0;
        LinkSignal::Instance().movePlayer(xSpeed, 0);
        break;
    case Qt::Key_Up:
        ySpeed = 0;
        LinkSignal::Instance().movePlayer(0, ySpeed);
        break;
    case Qt::Key_Down:
        ySpeed = 0;
        LinkSignal::Instance().movePlayer(0, ySpeed);
        break;
    default:
        break;
    }
}

