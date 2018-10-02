#ifndef ENEMYPLAYER_H
#define ENEMYPLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>

class EnemyPlayer : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    enum { Type = UserType + 2};
    EnemyPlayer(qreal posX, qreal posY);
    void advance(int phase);
private:
    const int speedPlayer = 5;
    int type() const;
    int xSpeed = 0;
    int ySpeed = 0;
    void collisionObjects();
    void movePlayer();
private slots:
    void onMoveEvent(int speedX, int speedY);
};

#endif // ENEMYPLAYER_H
