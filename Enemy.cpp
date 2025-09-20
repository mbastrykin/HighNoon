#include "Enemy.h"
#include <QTimer>
#include <QRandomGenerator>
#include <QDebug>

Enemy::Enemy(float x, float y, int reloadTime, QObject *parent)
    : QObject(parent),
    coordinateXP(x),
    coordinateYP(y),
    reloadTime(reloadTime)    // присваиваем
{
    // всегда полный магазин
    short int initialAmmo = magazineSize;

    weapon = new Weapon(initialAmmo, 6, magazineSize, this);

    // если на складе есть патроны — уменьшаем
    if (bulletsInInventory > 0) {
        short int toSub = std::min(bulletsInInventory, magazineSize);
        bulletsInInventory -= toSub;
    }

    connect(weapon, &Weapon::ammoChanged, this, &Enemy::ammoChanged);

    int startDelay = 5000;
    QTimer::singleShot(2000, this, [this, startDelay]() {
        QTimer *enemyTimer = new QTimer(this);
        connect(enemyTimer, &QTimer::timeout, this, &Enemy::shooting);
        enemyTimer->start(100);

    });
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

void Enemy::takeDamage(int dmg) {
    health -= dmg;
    qDebug() << "Enemy HP:" << health;

    if (health <= 0) {
        death();
        qDebug() << "Enemy died!";

    }
}

void Enemy::death(){
    m_color = "red";
    emit colorChanged();
}

void Enemy::animVictory() {}
