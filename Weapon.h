#pragma once
#include <QObject>

class Weapon : public QObject {
    Q_OBJECT
    Q_PROPERTY(int ammo READ ammo NOTIFY ammoChanged)

public:
    explicit Weapon(short int &ammo, QObject *parent = nullptr)
        : QObject(parent), ammoPtr(&ammo) {}

    int ammo() const { return *ammoPtr; }

    Q_INVOKABLE void shoot() {
        if (*ammoPtr > 0) {
            (*ammoPtr)--;
            emit ammoChanged();
        }
    }

signals:
    void ammoChanged();

private:
    short int *ammoPtr;
};
