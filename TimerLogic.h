#ifndef TIMERLOGIC_H
#define TIMERLOGIC_H

#endif // TIMERLOGIC_H


#pragma once
#include <QObject>

class TimerLogic : public QObject {
    Q_OBJECT
    Q_PROPERTY(int seconds READ seconds NOTIFY secondsChanged)

public:
    explicit TimerLogic(QObject *parent = nullptr) : QObject(parent), m_seconds(0) {}

    int seconds() const { return m_seconds; }

public slots:
    void tick() {
        m_seconds++;
        emit secondsChanged();
    }

signals:
    void secondsChanged();

private:
    int m_seconds;
};
