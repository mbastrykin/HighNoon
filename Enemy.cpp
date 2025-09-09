#include "Enemy.h"
#include <QTimer>
#include <QRandomGenerator>
#include <QDebug>

Enemy::Enemy(float x, float y, QObject *parent)
    : QObject(parent), coordinateXP(x), coordinateYP(y)
{

    short int initialAmmo = std::min(bulletsInInventory, magazineSize);
    weapon = new Weapon(initialAmmo, 70, magazineSize, this); // шанс оружия 70%
    bulletsInInventory -= initialAmmo;

    connect(weapon, &Weapon::ammoChanged, this, &Enemy::ammoChanged);

    // Таймер стрельбы врага
    QTimer *enemyTimer = new QTimer(this);
    connect(enemyTimer, &QTimer::timeout, this, &Enemy::shooting);
    enemyTimer->start(100); // каждые 100 мс
}

void Enemy::shooting() {
    if (reloading) return; // нельзя стрелять во время перезарядки

    if (weapon->getAmmo() > 0) {
        weapon->shoot();

        // проверка попадания
        int roll = QRandomGenerator::global()->bounded(100);
        int chanceToHit = (accuracy + weapon->getChanceOfHit()) / 2;

        if (roll < chanceToHit)
            emit hit();
        else
            emit miss();

        // анимация цвета при выстреле
        m_color = "blue";
        emit colorChanged();
        QTimer::singleShot(100, this, [this]() {
            m_color = "black";
            emit colorChanged();
        });
    }
    else if (!reloading && bulletsInInventory > 0) {
        // начинаем перезарядку
        reloading = true;
        QTimer::singleShot(reloadTime, this, [this]() {
            short int toLoad = std::min(bulletsInInventory, magazineSize);
            qDebug() << "Enemy is reloading";
            weapon->setAmmo(toLoad);
            bulletsInInventory -= toLoad;
            reloading = false;
        });
    }
}

void Enemy::stopShooting() {
    m_color = "black";
    emit colorChanged();
}

void Enemy::death() {
    lifeEnemy = false;
}

void Enemy::animVictory() {}
