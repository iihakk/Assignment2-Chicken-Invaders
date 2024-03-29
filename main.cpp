#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "player.h"
#include <QTimer>

Player* player;

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    QGraphicsScene* scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 800, 600);

    player = new Player();
    scene->addItem(player);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    player->setPos(scene->width() / 2 - player->pixmap().width() / 2, scene->height() - player->pixmap().height());

    QGraphicsView* view = new QGraphicsView(scene);
    view->setFixedSize(800, 600);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->show();

    scene->addItem(player->scoreDisplay);
    player->scoreDisplay->setPos(view->width() - 200, 10);
    scene->addItem(player->healthDisplay);
    player->healthDisplay->setPos(view->width() - 200, 30);

    QTimer* timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, player, &Player::createEnemy);
    timer->start(2000);

    return a.exec();
}
