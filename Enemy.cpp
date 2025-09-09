#include "Enemy.h"
#include <QTimer>
#include <QRandomGenerator>

Enemy::Enemy(float x, float y, QObject *parent)
    : QObject(parent), coordinateXP(x), coordinateYP(y)
{
    weapon = new Weapon(bullets, 70, 6,this); // шанс оружия 70%
    connect(weapon, &Weapon::ammoChanged, this, &Enemy::ammoChanged);

    // Таймер стрельбы врага
    QTimer *enemyTimer = new QTimer(this);
    connect(enemyTimer, &QTimer::timeout, this, &Enemy::shooting);
    enemyTimer->start(100); // каждые 100 мс
}

void Enemy::shooting() {
    if (weapon->getAmmo() > 0) {
        weapon->shoot(); // уменьшение патронов

        // проверка шанса попадания
        int roll = QRandomGenerator::global()->bounded(100);
        int chanceToHit = (accuracy + weapon->getChanceOfHit()) / 2;

        if (roll < chanceToHit)
            emit hit();
        else
            emit miss();

        // анимация выстрела
        m_color = "blue";
        emit colorChanged();
        QTimer::singleShot(100, this, [this]() {
            m_color = "black";
            emit colorChanged();
        });
    }

    if (weapon->getAmmo() <= 0) {
        weapon->setAmmo(bullets); // перезарядка
    }
}

void Enemy::stopShooting() {
    m_color = "black";
    emit colorChanged();
}

void Enemy::death() {
    lifeEnemy = false;
}

void Enemy::animVictory() {
}
