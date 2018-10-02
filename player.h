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
    const int speedPlayer = 5;
    int type() const;
    int xSpeed = 0;
    int ySpeed = 0;
    void collisionObjects();
    void movePlayer();
protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // PLAYER_H
