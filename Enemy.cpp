#include "Enemy.h"
#include <QTimer>
#include <QRandomGenerator>
#include <QDebug>

Enemy::Enemy(float x, float y, int reloadTime, QObject *parent)
    : QObject(parent),
    coordinateXP(x),
    coordinateYP(y),
    reloadTime(reloadTime)
{
    // магазин сразу полный
    short int initialAmmo = magazineSize;
    weapon = new Weapon(initialAmmo, 50, magazineSize, this);

    bulletsInInventory -= std::min(bulletsInInventory, magazineSize);

    connect(weapon, &Weapon::ammoChanged, this, &Enemy::ammoChanged);

    // Таймер автоматической стрельбы
    QTimer::singleShot(2000, this, [this]() {
        QTimer *enemyTimer = new QTimer(this);
        connect(enemyTimer, &QTimer::timeout, this, &Enemy::shooting);
      enemyTimer->start(100);
    });
}

void Enemy::shooting() {
    if (reloading || !lifeEnemy) return;

    if (weapon->getAmmo() > 0) {
        weapon->shoot();

        // проверка попадания
        int roll = QRandomGenerator::global()->bounded(100);
        int chanceToHit = (accuracy + weapon->getChanceOfHit()) / 2;

        if (roll < chanceToHit)
            emit hit();
        else
            emit miss();

        // Анимация цвета: синий при выстреле, зелёный если страх
        if (weapon->getAmmo() == 0) {
            m_color = "green";  // страх
            emit colorChanged();
            qDebug() << "Enemy is scared: magazine empty!";
        } else {
            m_color = "blue";   // обычный выстрел
            emit colorChanged();
            QTimer::singleShot(100, this, [this]() {
                m_color = "black";
                emit colorChanged();
            });
        }

    } else if (!reloading && bulletsInInventory > 0) {
        reloading = true;
        QTimer::singleShot(reloadTime, this, [this]() {
            short int toLoad = std::min(bulletsInInventory, magazineSize);
            weapon->setAmmo(toLoad);
            bulletsInInventory -= toLoad;
            reloading = false;
            qDebug() << "Enemy reloaded. Ammo:" << weapon->getAmmo();
        });
    }
}

void Enemy::fear() {
    if (weapon->getAmmo() == 0) {
        m_color = "green";
        emit colorChanged();
    }
}

void Enemy::stopShooting() {
    m_color = "black";
    emit colorChanged();
}

void Enemy::takeDamage(int dmg) {
    health -= dmg;
    qDebug() << "Enemy HP:" << health;
    if (health <= 0) death();
}

void Enemy::death() {
    lifeEnemy = false;
    m_color = "red";
    emit colorChanged();
    qDebug() << "Enemy died!";
}

void Enemy::victory() {}
