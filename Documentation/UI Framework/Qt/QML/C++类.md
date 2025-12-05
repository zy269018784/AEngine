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




QQuickWidget
    QQuickWidget does not support using windows as a root item.
    If you wish to create your root window from QML, consider using QQmlApplicationEngine instead.

QQuickView
    QQuickView does not support using a window as a root item.
    If you wish to create your root window from QML, consider using QQmlApplicationEngine instead.