#include <QWidget>
#include <QtQuickWidgets/QQuickWidget>
#include <QApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);  // Widgets 需要 QApplication
    
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("HelloQML.qml")));

    QWidget w;
    w.show();

    QQuickWidget *view = new QQuickWidget(&w);

    // 加载你的 QML 界面文件
    view->setSource(QUrl::fromLocalFile("CustomButton.qml"));

    // 显示它
    view->show();
    return app.exec();
}