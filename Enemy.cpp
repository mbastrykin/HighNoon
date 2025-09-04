#include "Enemy.h"
#include <QTimer>

Enemy::Enemy(float x, float y, QObject *parent)
    : QObject(parent), coordinateXP(x), coordinateYP(y)
{
    weapon = new Weapon(bullets, this);
    connect(weapon, &Weapon::ammoChanged, this, &Enemy::ammoChanged);

    QTimer *enemyTimer = new QTimer(this);
    connect(enemyTimer, &QTimer::timeout, this, &Enemy::shooting);
    enemyTimer->start(100);
}

void Enemy::shooting() {
    if (weapon->ammo() > 0) {
        weapon->shoot();
        m_color = "blue";
        emit colorChanged();

        // Вернуть цвет через 100 мс
        QTimer::singleShot(100, this, [this]() {
            m_color = "black";
            emit colorChanged();
        });
    }

}

void Enemy::stopShooting() {
    m_color = "black";      //Обратно в синий
    emit colorChanged();
}

void Enemy::death() {
    lifeEnemy = false;
}

void Enemy::animVictory() {
}
