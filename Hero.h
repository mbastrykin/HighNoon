#pragma once
#include <QObject>
#include <QString>
#include "Weapon.h"

class Hero : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString color READ color NOTIFY colorChanged)
    Q_PROPERTY(int ammo READ ammo NOTIFY ammoChanged)

public:
    explicit Hero(float x = 0, float y = 0, QObject *parent = nullptr);

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
    bool lifePlayer = true;
    bool reloading = false;
    int reloadTime = 2000; // мс

    float coordinateXP;
    float coordinateYP;

    QString m_color = "green";

    short int maxBullets = 24;  // максимальные патроны героя
    int accuracy = 50;          // меткость игрока (0–50%)

    Weapon *weapon;
};
