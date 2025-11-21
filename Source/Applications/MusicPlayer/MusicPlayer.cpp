#include <QGuiApplication>
#include <QQmlApplicationEngine>

int MusicPlayer(int argc, char** argv)
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("MusicPlayerWindow.qml")));

    return app.exec();
}