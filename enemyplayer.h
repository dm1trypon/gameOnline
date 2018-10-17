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
    const QString PATH_TO_ENEMYPLAYER_IMG = ":/img/enemy_player.png";

    qreal _posX = 0;
    qreal _posY = 0;
    int type() const;
    void collisionObjects();
    void movePlayer();
private slots:
    void slotOnMoveEvent(int posX, int posY);
};

#endif // ENEMYPLAYER_H
