#pragma once
#include <QObject>
#include <QString>
#include "Weapon.h"

class Enemy : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString color READ color NOTIFY colorChanged)
    Q_PROPERTY(int ammo READ ammo NOTIFY ammoChanged)

public:
    explicit Enemy(float x = 0, float y = 0, int reloadTime = 2000, QObject *parent = nullptr);

    QString color() const { return m_color; }
    int ammo() const { return weapon->getAmmo(); }

    Q_INVOKABLE void shooting();
    Q_INVOKABLE void stopShooting();
    Q_INVOKABLE void death();
    Q_INVOKABLE void victory();

public slots:
    void takeDamage(int dmg);

signals:
    void colorChanged();
    void ammoChanged();
    void hit();
    void miss();

private:
    void fear();

    bool lifeEnemy = true;
    bool reloading = false;

    int reloadTime; // мс
    int accuracy = 50;
    int health = 150;

    float coordinateXP;
    float coordinateYP;

    short int bulletsInInventory = 12;
    short int magazineSize = 6;

    QString m_color = "black";

    Weapon *weapon;
};
