#include "widget.h"
#include "ui_widget.h"
#include "player.h"
#include "enemyplayer.h"
#include "linksignal.h"
#include "client.h"

#include <QDebug>
#include <QKeyEvent>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->graphicsView->hide();
    createEnter();
    connect(_enterNickName, SIGNAL(returnPressed()), this, SLOT(newGame()));
}

Widget::~Widget()
{
    animationTimer->stop();
    delete ui;
}

void Widget::newGame()
{
    LinkSignal::Instance().getNickName(_enterNickName->text());
    _enterNickName->hide();
    ui->graphicsView->show();
    createScene();
    timers();
    connections();
}

void Widget::createEnter()
{
    _enterNickName = new QLineEdit("", this);
    _enterNickName->setMaxLength(15);
    _enterNickName->setPlaceholderText("Insert your nickname...");
    _enterNickName->setStyleSheet("font: 25px");
    _enterNickName->setGeometry(QRect(QPoint(100, 100), QSize(300, 50)));
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

void Widget::createEnemyPlayer(qreal posX, qreal posY)
{
    EnemyPlayer *enemyPlayer_ = new EnemyPlayer(posX, posY);
    scene->addItem(enemyPlayer_);
    qDebug() << "ENEMY PLAYER DATA: POSX:" << enemyPlayer_->pos().x() << "POSY:" << enemyPlayer_->pos().y();
}

void Widget::createPlayer()
{
    srand(static_cast<uint>(time(nullptr)));
    qreal setX = rand() % (SCENE_WIDTH);
    qreal setY = rand() % (SCENE_HEIGHT);
    qDebug() << "Player has been created!";
    Player *player_ = new Player(setX, setY);
    scene->addItem(player_);
    LinkSignal::Instance().positionPlayer(setX, setY);
}
