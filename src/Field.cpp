#include "include/Field.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>

Field::Field(QObject *parent)
	: QObject{ parent }
{
}

void Field::loadStage(const int num)
{
	QFile file{ QString{"://stage/stage-%1.dat"}.arg(num) };
	file.open(QFile::ReadOnly | QFile::Text);

	QTextStream in(&file);
	while (!in.atEnd()) {
		const QString line = in.readLine();

		QVector<QChar> vec(line.size());
		for (int i = 0; i < line.size(); ++i) {
			vec.push_back(line[i]);
		}

		_field.push_back(std::move(vec));
	}
}
