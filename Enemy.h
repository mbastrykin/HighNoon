#pragma once
#include <QObject>
#include <QString>
#include "Weapon.h"

class Enemy : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString color READ color NOTIFY colorChanged)
    Q_PROPERTY(int ammo READ ammo NOTIFY ammoChanged)

public:
    explicit Enemy(float x = 0, float y = 0, QObject *parent = nullptr);

    QString color() const { return m_color; }
    int ammo() const { return weapon->getAmmo(); }

    Q_INVOKABLE void shooting();
    Q_INVOKABLE void stopShooting();
    Q_INVOKABLE void death();
    Q_INVOKABLE void animVictory();

signals:
    void colorChanged();
    void ammoChanged();
    void hit();
    void miss();

private:
    bool lifeEnemy = true;
    bool reloading = false;

    int reloadTime = 2500; // мс
    int accuracy = 50;                 // меткость врага (0–100%)

    float coordinateXP;
    float coordinateYP;

    short int bulletsInInventory = 24; // патроны врага в инвентаре
    short int magazineSize = 6;        // вместимость магазина

    QString m_color = "black";

    Weapon *weapon;
};
