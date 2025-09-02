#include "Enemy.h"
#include <QTimer>

Enemy::Enemy(float x, float y, QObject *parent)
    : QObject(parent), coordinateXP(x), coordinateYP(y)
{
    weapon = new Weapon(bullets, this);
    connect(weapon, &Weapon::ammoChanged, this, &Enemy::ammoChanged);
}

void Enemy::shooting() {
    if (weapon->ammo() > 0) {
        weapon->shoot();
        m_color = "blue";
        emit colorChanged();

        // Вернуть цвет через 200 мс
        QTimer::singleShot(100, this, [this]() {
            m_color = "black";
            emit colorChanged();
        });
    }
}

void Enemy::stopShooting() {
    m_color = "blue";      //Обратно в синий
    emit colorChanged();
}

void Enemy::death() {
    lifeEnemy = false;
}

void Enemy::animVictory() {
}
