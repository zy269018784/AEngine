#if PROJECT_USE_QT
    #include <QGuiApplication>
    #include <QQmlApplicationEngine>
#endif
#if PROJECT_USE_SFML
    #include <SFML/Audio.hpp>
    #include <SFML/Graphics.hpp>
    #include <SFML/Audio/Music.hpp>
#endif
#include <iostream>
int MusicPlayer(int argc, char** argv)
{
#if PROJECT_USE_QT
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("MusicPlayerWindow.qml")));
    return app.exec();
#else
    return 0;
#endif
}

int Play(char *file)
{
#if PROJECT_USE_SFML
    //auto Music = new sf::Music("ikutaerika.mp3");
    auto Music = new sf::Music("1，ogg");
#endif
    std::cout << "play start" << std::endl;
#if PROJECT_USE_SFML
    Music->play();
#endif
    std::cout << "play end" << std::endl;
    while (1);
    return 0;
}