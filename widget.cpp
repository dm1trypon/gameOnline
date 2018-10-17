#include "widget.h"
#include "ui_widget.h"
#include "player.h"
#include "enemyplayer.h"
#include "linksignal.h"
#include "client.h"

#include <QDebug>
#include <QKeyEvent>
#include <QLayout>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->verticalLayout->setMargin(0);
    ui->graphicsView->hide();
    createEnter();
    connect(_enterNickName, &QLineEdit::returnPressed, this, &Widget::slotNewGame);
}

Widget::~Widget()
{
    animationTimer->stop();
    delete ui;
}

void Widget::slotNewGame()
{
    qDebug() << "Your login is" << _enterNickName->text() << ". Welcome to gamefield!";
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
    scene = new QGraphicsScene(0, 0,
                               ui->graphicsView->width() - PADDING,
                               ui->graphicsView->height() - PADDING, this);
    scene->setStickyFocus(true);
    QPixmap pim(PATH_TO_BG_IMG);
    scene->setBackgroundBrush(pim.scaled(ui->graphicsView->width() - 10,
                                         ui->graphicsView->height() - 10,
                                         Qt::IgnoreAspectRatio,
                                         Qt::SmoothTransformation));
    ui->graphicsView->setScene(scene);
    qDebug() << "Scene has been created!";
}

void Widget::timers()
{
    animationTimer = new QTimer(this);
    animationTimer->start(TIME_ANIMATION);
    qDebug() << "Timers runing!";
}

void Widget::connections()
{
    connect(animationTimer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    connect(&LinkSignal::Instance(), &LinkSignal::signalConnectedToServer, this, &Widget::slotCreatePlayer);
    connect(&LinkSignal::Instance(), &LinkSignal::signalCreateEnemyPlayer, this, &Widget::slotCreateEnemyPlayer);
}

void Widget::slotCreateEnemyPlayer(qreal posX, qreal posY)
{
    EnemyPlayer *enemyPlayer_ = new EnemyPlayer(posX, posY);
    scene->addItem(enemyPlayer_);
    enemyPlayer_->setPos(posX, posY);
}

void Widget::slotCreatePlayer()
{
    srand(static_cast<uint>(time(nullptr)));
    qreal setX = rand() % (SCENE_WIDTH);
    qreal setY = rand() % (SCENE_HEIGHT);
    Player *player_ = new Player(setX, setY);
    scene->addItem(player_);
    LinkSignal::Instance().positionPlayer(setX, setY);
}
