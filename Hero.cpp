#include "Hero.h"
#include <QTimer>
#include <QRandomGenerator>
#include <QDebug>

Hero::Hero(float x, float y, QObject *parent)
    : QObject(parent), coordinateXP(x), coordinateYP(y)
{
    short int initialAmmo = 24; // сразу полный магазин
    weapon = new Weapon(initialAmmo, 80, 6, this);
    connect(weapon, &Weapon::ammoChanged, this, &Hero::ammoChanged);
}

void Hero::shooting() {
    if (reloading || !lifePlayer) return;

    if (weapon->getAmmo() > 0) {
        weapon->shoot();

        int roll = QRandomGenerator::global()->bounded(100);
        int chanceToHit = (accuracy + weapon->getChanceOfHit()) / 2;

        if (roll < chanceToHit) {
            emit hit();
            if (targetEnemy) targetEnemy->takeDamage(weapon->getDamage());
        } else emit miss();

        m_color = "red";
        emit colorChanged();
        QTimer::singleShot(100, this, [this]() {
            m_color = "green";
            emit colorChanged();
        });

    } else if (!reloading && maxBullets > 0) {
        reloading = true;
        QTimer::singleShot(reloadTime, this, [this]() {
            short int toLoad = std::min(maxBullets, weapon->getMagazineSize());
            weapon->setAmmo(toLoad);
            maxBullets -= toLoad;
            reloading = false;
            qDebug() << "Hero reloaded. Ammo:" << weapon->getAmmo();
        });
    }
}

void Hero::stopShooting() {
    m_color = "green";
    emit colorChanged();
}

void Hero::death() {
    lifePlayer = false;
    m_color = "red";
    emit colorChanged();
}

void Hero::animVictory() {}
