#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTimer>
#include "TimerLogic.h"
#include "Hero.cpp"


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    TimerLogic timerLogic;
    engine.rootContext()->setContextProperty("timerLogic", &timerLogic);

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
