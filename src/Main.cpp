#include "include/Game.h"

#include <QDebug>

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	try {
		return Game{ argc, argv }.exec();
	} catch (const std::exception& e) {
		qDebug() << e.what();
	} catch (...) {
		qDebug() << QStringLiteral("Unhandled exception has been occurred");
	}
}
