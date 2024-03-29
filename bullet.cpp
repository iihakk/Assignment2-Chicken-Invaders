#include "bullet.h"
#include <QGraphicsScene>
#include <QTimer>
#include <QList>
#include "enemy.h"
#include <typeinfo>
#include "player.h"

extern Player* player;

Bullet::Bullet() : QObject(), QGraphicsPixmapItem() {
    setPixmap(QPixmap(":/images/laser.png").scaled(10, 50));

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Bullet::move);
    timer->start(50);
}

void Bullet::move() {
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for (int i = 0; i < colliding_items.size(); ++i) {
        if (typeid(*(colliding_items[i])) == typeid(Enemy)) {
            player->increaseScore();

            QSoundEffect* effect = new QSoundEffect;
            effect->setSource(QUrl("qrc:/sounds/chicken.wav"));
            effect->play();

            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            delete colliding_items[i];
            delete this;
            return;
        }
    }

    setPos(x(), y() - 10);
    if (pos().y() + pixmap().height() < 0) {
        scene()->removeItem(this);
        delete this;
    }
}
