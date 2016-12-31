#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "include/KeyEventFilter.h"
#include "include/UserInput.h"

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	QGuiApplication app{ argc, argv };

	UserInput ui;
	KeyEventFilter kef;
	QObject::connect(&kef, &KeyEventFilter::Send, &ui, &UserInput::OnReceive);
	app.installEventFilter(&kef);

	QQmlApplicationEngine engine;
	engine.load(QUrl(QLatin1String("qrc:/qml/Main.qml")));

	return app.exec();
}
