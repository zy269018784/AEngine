/*
	1. 
		QQuickWidget				QML控件
		QQuickWindow				QML窗口
		QQuickPaintedItem	
		QQmlEngine					QML引擎
		QQmlContext					QML上下文
		QQmlComponent				
		QQmlExpression				QML表达式	
		QQuickItem
		QQuickView
		QQuickImageProvider
		QQmlApplicationEngine
	2. QQmlEngine
		QQmlContext *rootContext() const

	3. QQmlExpression
		QML:
			import QtQuick 2.0
			Item {
				width: 200; height: 200
			}
		C++:
			QQmlEngine *engine = new QQmlEngine;
			QQmlComponent component(engine, QUrl::fromLocalFile("main.qml"));
			QObject *myObject = component.create();
			QQmlExpression *expr = new QQmlExpression(engine->rootContext(), myObject, "width * 2");
			int result = expr->evaluate().toInt();  // result = 400

	4. QQmlComponent
	C++:
		QQmlEngine *engine = new QQmlEngine;
		QQmlComponent component(engine, QUrl::fromLocalFile("main.qml"));
		if (component.isError()) {
			qWarning() << "Failed to load main.qml:" << component.errors();
			return 1;
		}

		QObject *myObject = component.create();
		if (component.isError()) {
			qWarning() << "Failed to create instance of main.qml:" << component.errors();
			return 1;
		}

		QQuickItem *item = qobject_cast<QQuickItem*>(myObject);
		int width = item->width();  // width = 200

	5. QML & C++
		5.1 QML可以访问QObject的Properties, Methods, Signals.
		5.2 Any QObject-derived C++ class can be registered as the definition of a QML object type.
			QML_ELEMENT 
			QML_NAMED_ELEMENT(<name>)
	
*/