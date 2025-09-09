#include "Weapon.h"
#include <QRandomGenerator>

Weapon::Weapon(short int &ammo, short int chanceOfHit, short int magSize, QObject *parent)
    : QObject(parent),
    ammoPtr(&ammo),
    m_chanceOfHit(chanceOfHit),
    magazineSize(magSize) // инициализация члена
{
}

int Weapon::getAmmo() const {
    return *ammoPtr;
}

void Weapon::setAmmo(int value) {
    *ammoPtr = value;
    emit ammoChanged();
}

int Weapon::getChanceOfHit() const {
    return m_chanceOfHit;
}

bool Weapon::shoot() {
    if (*ammoPtr > 0) {
        (*ammoPtr)--;
        emit ammoChanged();

        int roll = QRandomGenerator::global()->bounded(100); // 0..99
        return roll < m_chanceOfHit; // true = попал
    }
    return false; // нет патронов — не выстрелил
}
