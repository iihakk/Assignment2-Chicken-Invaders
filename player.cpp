#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QMessageBox>
#include <QSoundEffect>

Player::Player() : health(3), score(0), isGameOver(false) {
    setPixmap(QPixmap(":/images/ship.png").scaled(100, 100));

    scoreDisplay = new QGraphicsTextItem("Score: 0");
    scoreDisplay->setDefaultTextColor(Qt::red);
    scoreDisplay->setFont(QFont("times", 16));
    scoreDisplay->setZValue(1);

    healthDisplay = new QGraphicsTextItem("Health: 3");
    healthDisplay->setDefaultTextColor(Qt::red);
    healthDisplay->setFont(QFont("times", 16));
    healthDisplay->setZValue(1);


    bulletSound = new QSoundEffect(this);
    bulletSound->setSource(QUrl("qrc:/sounds/laser.wav"));
}

void Player::keyPressEvent(QKeyEvent *event) {
    if (isGameOver) {
        return;
    }


    const int moveDistance = 10;
    // Boundaries
    const int leftLimit = 0;
    const int rightLimit = 800 - this->pixmap().width();

    if (event->key() == Qt::Key_Left) {
        if (pos().x() > leftLimit) {
            setPos(x() - moveDistance, y());
        }
    } else if (event->key() == Qt::Key_Right) {
        if (pos().x() < rightLimit) {
            setPos(x() + moveDistance, y());
        }
    } else if (event->key() == Qt::Key_Space) {
        // Create and shoot a bullet
        Bullet* bullet = new Bullet();
        bullet->setPos(x() + pixmap().width() / 2 - bullet->pixmap().width() / 2, y() - bullet->pixmap().height());
        scene()->addItem(bullet);


        bulletSound->play();
    }
}

void Player::createEnemy() {
    if (!isGameOver) {
        Enemy* enemy = new Enemy();
        scene()->addItem(enemy);
    }
}

void Player::decreaseHealth() {
    health--;
    updateHealth();
    if (health <= 0 && !isGameOver) {
        isGameOver = true;
        QMessageBox::information(nullptr, "Game Over", "Your final score is: " + QString::number(score));

    }
}

void Player::increaseScore() {
    score++;
    updateScore();
}

void Player::updateScore() {
    scoreDisplay->setPlainText("Score: " + QString::number(score));
}

void Player::updateHealth() {
    healthDisplay->setPlainText("Health: " + QString::number(health));
}
