#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
#include <iostream>
int MusicPlayer(int argc, char** argv)
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("MusicPlayerWindow.qml")));

    return app.exec();
}

int Play(char *file)
{
    auto Music = new sf::Music("ikutaerika.mp3");
    std::cout << "play start" << std::endl;
    Music->play();
    std::cout << "play end" << std::endl;
    while (1);
    return 0;
}