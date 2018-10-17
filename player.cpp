#include "player.h"
#include "widget.h"
#include "linksignal.h"

#include <QDebug>

Player::Player(qreal posX, qreal posY) : QObject(), QGraphicsPixmapItem (nullptr)
{
    setPixmap(QPixmap(PATH_TO_PLAYER_IMG));
    setPos(posX, posY);
    qDebug() << "Player has been created (" << posX << ";" << posY << ")";
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
}

void Player::advance(int phase)
{
    if (phase <= 0) {
        collisionObjects();
    }
    if (onFrame(phase)) {
        movePlayer();
    }
    if (!onFrame(phase)) {
        stabilizeMove();
    }
}

int Player::type() const
{
    return Type;
}

bool Player::onFrame(int phase)
{
    return phase >= 1 && LinkSignal::Instance().onFrameBoard(getPostionX(), getPostionY());
}

void Player::movePlayer()
{
    moveBy(xSpeed, ySpeed);
    if ((xSpeed) || (ySpeed))
    {
        qDebug() << "Move player (" << getPostionX() << ";" << getPostionY() << ")";
        LinkSignal::Instance().movePlayer(getPostionX(), getPostionY());
    }
}
void Player::collisionObjects()
{

}

QString Player::getSideName()
{
    if (getPostionX() <= 0)
    {
        qDebug() << "Warning, left side";
        return LEFT;
    }
    if (this->pos().x() >= SCENE_WIDTH)
    {
        qDebug() << "Warning, right side";
        return RIGHT;
    }
    if (this->pos().y() >= SCENE_HEIGHT)
    {
        qDebug() << "Warning, bottom side";
        return BOTTOM;
    }
    if (this->pos().y() <= 0)
    {
        qDebug() << "Warning, top side";
        return TOP;
    }
    return "";
}

qreal Player::getPostionX()
{
    return this->pos().x();
}

qreal Player::getPostionY()
{
    return this->pos().y();
}

void Player::stabilizeMove()
{
    if (getSideName() == LEFT)
        this->setPos(getPostionX() + STABILIZE, getPostionY());

    if (getSideName() == RIGHT)
        this->setPos(getPostionX() - STABILIZE, getPostionY());

    if (getSideName() == TOP)
        this->setPos(getPostionX(), getPostionY() + STABILIZE);

    if (getSideName() == BOTTOM)
        this->setPos(getPostionX(), getPostionY() - STABILIZE);
}

void Player::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        xSpeed = - SPEED_PLAYER;
        break;
    case Qt::Key_Right:
        xSpeed = SPEED_PLAYER;
        break;
    case Qt::Key_Up:
        ySpeed = - SPEED_PLAYER;
        break;
    case Qt::Key_Down:
        ySpeed = SPEED_PLAYER;
        break;
    default:
        break;
    }
}

void Player::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        xSpeed = 0;
        break;
    case Qt::Key_Right:
        xSpeed = 0;
        break;
    case Qt::Key_Up:
        ySpeed = 0;
        break;
    case Qt::Key_Down:
        ySpeed = 0;
        break;
    default:
        break;
    }
}
