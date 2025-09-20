#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTimer>
#include "TimerLogic.h"
#include "Hero.h"
#include "Enemy.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    TimerLogic timerLogic;
    engine.rootContext()->setContextProperty("timerLogic", &timerLogic);

    Hero hero(100, 100);
    Enemy enemy(100,100, 1000);

    hero.targetEnemy = &enemy;

    QObject::connect(&hero, &Hero::hit, [&enemy, &hero](){
        enemy.takeDamage(hero.weapon->getDamage());
    });

    // Вывод в консоль (тест)
    QObject::connect(&hero, &Hero::hit, [](){
        qDebug() << "Hero: Hit!";
    });
    QObject::connect(&hero, &Hero::miss, [](){
        qDebug() << "Hero: Miss!";
    });

    // Вывод в консоль (тест)
    QObject::connect(&enemy, &Enemy::hit, [](){
        qDebug() << "Enemy: Hit!";
    });
    QObject::connect(&enemy, &Enemy::miss, [](){
        qDebug() << "Enemy: Miss!";
    });

    engine.rootContext()->setContextProperty("hero", &hero); // <<< имя "hero"
    engine.rootContext()->setContextProperty("enemy", &enemy);

    // Создаём QTimer, который каждую секунду вызывает tick()
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, &timerLogic, &TimerLogic::tick);

    timer.start(1000);

    const QUrl url(u"qrc:/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                         if (!obj && url == objUrl)
                             QCoreApplication::exit(-1);
                     }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
