#include <QApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);  // Widgets 需要 QApplication
    
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("HelloQML.qml")));
    
    return app.exec();
}