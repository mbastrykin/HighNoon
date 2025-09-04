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
    int ammo() const { return weapon->ammo(); }

    Q_INVOKABLE void shooting();
    Q_INVOKABLE void stopShooting();   // <-- добавляем
    Q_INVOKABLE void death();
    Q_INVOKABLE void animVictory();



signals:
    void colorChanged();
    void ammoChanged();

private:
    bool lifeEnemy = true;
    float coordinateXP;
    float coordinateYP;
    QString m_color = "black";

    short int bullets = 6;
    Weapon *weapon;
};
