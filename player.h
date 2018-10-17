#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>

class Player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    enum { Type = UserType + 1};
    Player(qreal posX, qreal posY);
    void advance(int phase);
private:
    const int SPEED_PLAYER = 5;
    const int STABILIZE = 2;
    const QString PATH_TO_PLAYER_IMG = ":/img/player.png";
    const QString LEFT = "left";
    const QString RIGHT = "right";
    const QString TOP = "top";
    const QString BOTTOM = "bottom";

    int xSpeed = 0;
    int ySpeed = 0;
    int type() const;
    void collisionObjects();
    void movePlayer();
    bool onFrame(int phase);
    void stabilizeMove();
    QString getSideName();
    qreal getPostionX();
    qreal getPostionY();
protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // PLAYER_H
