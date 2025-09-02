#include "Hero.h"

Hero::Hero(float x, float y, QObject *parent)
    : QObject(parent), coordinateXP(x), coordinateYP(y)
{
    weapon = new Weapon(bullets, this);
    connect(weapon, &Weapon::ammoChanged, this, &Hero::ammoChanged);
}

void Hero::shooting() {
    if (weapon->ammo() > 0) {
        weapon->shoot();
        m_color = "red";      // красный во время нажатия
        emit colorChanged();
    }
}

void Hero::stopShooting() {
    m_color = "green";        // обратно в зелёный
    emit colorChanged();
}

void Hero::death() {
    lifePlayer = false;
}

void Hero::animVictory() {
}
