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
    void hit();   // попал
    void miss();  // промах

private:
    bool lifeEnemy = true;
    float coordinateXP;
    float coordinateYP;

    QString m_color = "black";

    short int bullets = 6;
    int accuracy = 50; // меткость врага (0–100%)

    Weapon *weapon;
};
