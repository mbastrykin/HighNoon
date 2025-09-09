#pragma once
#include <QObject>

class Weapon : public QObject {
    Q_OBJECT
    Q_PROPERTY(int ammo READ getAmmo NOTIFY ammoChanged)

public:
    explicit Weapon(short int &ammo, short int chanceOfHit, QObject *parent = nullptr);

    int getAmmo() const;
    void setAmmo(int value);
    int getChanceOfHit() const;

    Q_INVOKABLE bool shoot();   // true = попал, false = промах

signals:
    void ammoChanged();

private:
    short int *ammoPtr;        // ссылка на патроны
    short int m_chanceOfHit;   // шанс попадания (0–100%)
};
