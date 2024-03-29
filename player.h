#ifndef PLAYER_H
#define PLAYER_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QKeyEvent>
#include <QGraphicsTextItem>
#include <QSoundEffect>

class Player : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Player();
    void keyPressEvent(QKeyEvent *event);
    void updateScore();
    void updateHealth();
    QGraphicsTextItem* scoreDisplay;
    QGraphicsTextItem* healthDisplay;
    bool isGameOver;

    QSoundEffect* bulletSound;

public slots:
    void createEnemy();
    void decreaseHealth();
    void increaseScore();

private:
    int health;
    int score;
};

#endif // PLAYER_H
