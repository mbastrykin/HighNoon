#include "Hero.h"
#include <QTimer>
#include <QRandomGenerator>

Hero::Hero(float x, float y, QObject *parent)
    : QObject(parent), coordinateXP(x), coordinateYP(y)
{
    weapon = new Weapon(bullets, 80, this); // 80% базовый шанс оружия
    connect(weapon, &Weapon::ammoChanged, this, &Hero::ammoChanged);
}

void Hero::shooting() {
    if (weapon->getAmmo() > 0) {
        weapon->shoot(); // уменьшение патронов

        // проверка шанса попадания
        int roll = QRandomGenerator::global()->bounded(100);
        int chanceToHit = (accuracy + weapon->getChanceOfHit()) / 2;

        if (roll < chanceToHit)
            emit hit();
        else
            emit miss();

        // анимация выстрела (красный на 100 мс)
        m_color = "red";
        emit colorChanged();
        QTimer::singleShot(100, this, [this]() {
            m_color = "green";
            emit colorChanged();
        });
    }

    // перезарядка, если патронов нет
    if (weapon->getAmmo() <= 0) {
        weapon->setAmmo(bullets);
    }
}

void Hero::stopShooting() {
    m_color = "green";
    emit colorChanged();
}

void Hero::death() {
    lifePlayer = false;
}

void Hero::animVictory() {
}
