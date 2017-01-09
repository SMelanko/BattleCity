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
		_field.push_back(in.readLine());
	}
}
