#ifdef PROJECT_USE_QT
    #include <QGuiApplication>
    #include <QQmlApplicationEngine>
#endif
#ifdef PROJECT_USE_SFML
    #include <SFML/Audio.hpp>
    #include <SFML/Graphics.hpp>
    #include <SFML/Audio/Music.hpp>
#endif
#include <iostream>
int MusicPlayer(int argc, char** argv)
{
#ifdef PROJECT_USE_QT
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
#ifdef PROJECT_USE_SFML
    auto Music = new sf::Music("ikutaerika.mp3");
#endif
    std::cout << "play start" << std::endl;
#ifdef PROJECT_USE_SFML
    Music->play();
#endif
    std::cout << "play end" << std::endl;
    while (1);
    return 0;
}