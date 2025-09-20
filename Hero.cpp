#include "Hero.h"
#include <QTimer>
#include <QRandomGenerator>
#include <QDebug>

Hero::Hero(float x, float y, QObject *parent)
    : QObject(parent), coordinateXP(x), coordinateYP(y)
{

    short int currentAmmo = maxBullets;
    weapon = new Weapon(currentAmmo, 80, 6,this); // шанс попадания 80%
    connect(weapon, &Weapon::ammoChanged, this, &Hero::ammoChanged);
}

void Hero::shooting() {
    if (reloading) return; // пока перезаряжаемся — стрелять нельзя

    if (weapon->getAmmo() > 0) {
        weapon->shoot();

        // проверка попадания
        int roll = QRandomGenerator::global()->bounded(100);
        int chanceToHit = (accuracy + weapon->getChanceOfHit()) / 2;

        if (roll < chanceToHit) {
            emit hit();
            if (targetEnemy) {
                targetEnemy->takeDamage(weapon->getDamage());
            }
        }
        else
            emit miss();
        // анимация цвета
        m_color = "red";
        emit colorChanged();
        QTimer::singleShot(100, this, [this]() {
            m_color = "green";
            emit colorChanged();
        });
    }
    else if (!reloading) {
        if (maxBullets == 0) {
            qDebug() << "No bullets left in inventory!";
            return;
        }

        reloading = true;
        qDebug() << "Reloading...";
        QTimer::singleShot(reloadTime, this, [this]() {

            short int toLoad = std::min(maxBullets, weapon->getMagazineSize());
            weapon->setAmmo(toLoad);
            maxBullets -= toLoad;

            reloading = false;
            qDebug() << "Reload complete";
            qDebug() << "Ammo after reload:" << weapon->getAmmo();
            qDebug() << "Bullets left in inventory:" << maxBullets;
        });
    }

}

void Hero::stopShooting() {
    m_color = "green";
    emit colorChanged();
}

void Hero::death() { lifePlayer = false; }
void Hero::animVictory() {}
