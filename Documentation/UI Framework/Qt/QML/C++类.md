重要类:
    QQmlContext
    QQmlEngine
    QQmlApplicationEngine
    QQmlComponent
    QQmlProperty
    QQuickView
    QQuickWidget

QQmlApplicationEngine
    QList<QObject *> rootObjects() const    获取根对象列表

QQuickWidget
    QQmlContext *rootContext() const
    QQuickItem *rootObject() const

例子:
    1. 从QML创建QObject
        QQmlEngine engine;
        QQmlComponent component(&engine,
        QUrl::fromLocalFile("MyItem.qml"));
        QObject *object = component.create();

    2.
        // Using QQuickView
        QQuickView view;
        view.setSource(QUrl::fromLocalFile("MyItem.qml"));
        view.show();
        QObject *object = view.rootObject();




    