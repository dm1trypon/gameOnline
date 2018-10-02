#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QTimer>
#include <QKeyEvent>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void createPlayer();
    void createEnemyPlayer(qreal posX, qreal poxY);
private:
    const int SCENE_WIDTH = 1920;
    const int SCENE_HEIGHT = 1080;
    const int TIME_ANIMATION = 1000/60;
    Ui::Widget *ui;
    QGraphicsScene* scene;
    QTimer *animationTimer;
    void createScene();
    void timers();
    void connections();
};

#endif // WIDGET_H
