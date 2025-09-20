#pragma once
#include <QObject>

class Weapon : public QObject {
    Q_OBJECT
    Q_PROPERTY(int ammo READ getAmmo NOTIFY ammoChanged)

public:
    explicit Weapon(short int &ammo, short int chanceOfHit, short int magazineSize, QObject *parent = nullptr);

    int getAmmo() const;
    short int getMagazineSize() const { return magazineSize; }
    void setAmmo(int value);
    int getChanceOfHit() const;

    Q_INVOKABLE bool shoot();   // true = попал, false = промах
    int getDamage() const { return damage; } // добавляем метод для урона

signals:
    void ammoChanged();

private:
    short int magazineSize;
    short int *ammoPtr;        // указатель на патроны
    short int m_chanceOfHit;   // шанс попадания (0–100%)
    int damage = 50;           // урон за выстрел
};
