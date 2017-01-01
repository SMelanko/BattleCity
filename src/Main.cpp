#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "include/KeyEventFilter.h"
#include "include/Game.h"

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	QGuiApplication app{ argc, argv };

	KeyEventFilter kef;
	app.installEventFilter(&kef);

	Game g(&kef);
	g.Play();

	QQmlApplicationEngine engine;
	engine.load(QUrl(QLatin1String("qrc:/qml/Main.qml")));

	return app.exec();
}
