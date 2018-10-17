#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QTimer>
#include <QKeyEvent>
#include <QLineEdit>

const int SCENE_WIDTH = 1820;
const int SCENE_HEIGHT = 980;

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
    void slotCreatePlayer();
    void slotCreateEnemyPlayer(qreal posX, qreal posY);
    void slotNewGame();
private:
    const int TIME_ANIMATION = 1000/60;
    const int PADDING = 10;
    const QString PATH_TO_BG_IMG = ":/img/bg.jpg";

    QLineEdit *_enterNickName;
    Ui::Widget *ui;
    QGraphicsScene* scene;
    QTimer *animationTimer;
    void createScene();
    void timers();
    void connections();
    void createEnter();
};

#endif // WIDGET_H
