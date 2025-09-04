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
    int ammo() const { return weapon->ammo(); }

    Q_INVOKABLE void shooting();
    Q_INVOKABLE void stopShooting();
    Q_INVOKABLE void death();
    Q_INVOKABLE void animVictory();

signals:
    void colorChanged();
    void ammoChanged();

private:
    bool lifePlayer = true;
    float coordinateXP;
    float coordinateYP;
    QString m_color = "green";

    short int bullets = 12;
    Weapon *weapon;
};
