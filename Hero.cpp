#include "Hero.h"
#include <QTimer>

Hero::Hero(float x, float y, QObject *parent)
    : QObject(parent), coordinateXP(x), coordinateYP(y)
{
    weapon = new Weapon(bullets, this);
    connect(weapon, &Weapon::ammoChanged, this, &Hero::ammoChanged);
}

void Hero::shooting() {
    if (weapon->ammo() > 0) {
        weapon->shoot();
        m_color = "red";
        emit colorChanged();

        // Вернуть цвет через 100 мс
        QTimer::singleShot(100, this, [this]() {
            m_color = "green";
            emit colorChanged();
        });
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
