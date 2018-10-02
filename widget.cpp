#include "widget.h"
#include "ui_widget.h"
#include "player.h"
#include "enemyplayer.h"
#include "linksignal.h"

#include <QDebug>
#include <QKeyEvent>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    createScene();
    timers();
    connections();
}

Widget::~Widget()
{
    animationTimer->stop();
    delete ui;
}

void Widget::createScene()
{
    scene = new QGraphicsScene(0, 0, SCENE_WIDTH, SCENE_HEIGHT, this);
    scene->setStickyFocus(true);
    QPixmap pim(":/img/bg.jpg");
    scene->setBackgroundBrush(pim.scaled(SCENE_WIDTH, SCENE_HEIGHT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    ui->graphicsView->setScene(scene);
}

void Widget::timers()
{
    animationTimer = new QTimer(this);
    animationTimer->start(TIME_ANIMATION);
}

void Widget::connections()
{
    connect(animationTimer, SIGNAL(timeout()), scene, SLOT(advance()));
    connect(&LinkSignal::Instance(), SIGNAL(signalConnectedToServer()), this, SLOT(createPlayer()));
    connect(&LinkSignal::Instance(), SIGNAL(signalCreateEnemyPlayer(qreal, qreal)), this, SLOT(createEnemyPlayer(qreal, qreal)));
}

void Widget::createEnemyPlayer(qreal posX, qreal poxY)
{
    EnemyPlayer *enemyPlayer_ = new EnemyPlayer(posX, poxY);
    scene->addItem(enemyPlayer_);
}

void Widget::createPlayer()
{
    srand(static_cast<uint>(time(nullptr)));
    qreal setX = rand() % (SCENE_WIDTH);
    qreal setY = rand() % (SCENE_HEIGHT);
    qDebug() << setX << setY;
    Player *player_ = new Player(setX, setY);
    scene->addItem(player_);
    LinkSignal::Instance().positionPlayer(setX, setY);
}
