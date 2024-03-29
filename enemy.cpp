#include "enemy.h"
#include <QGraphicsScene>
#include <stdlib.h>
#include <QTimer>
#include "player.h"

extern Player* player;

Enemy::Enemy() {
    setPixmap(QPixmap(":/images/chicken.png").scaled(100, 100));

    int random_number = rand() % 700;
    setPos(random_number, 0);

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Enemy::move);
    timer->start(50);
}

void Enemy::move() {
    setPos(x(), y() + 5);
    if (pos().y() > 600) {
        if (player->isGameOver) {
            return; //
        }

        player->decreaseHealth();
        scene()->removeItem(this);
        delete this;
    }
}
