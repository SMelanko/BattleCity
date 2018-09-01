#include "include/Field.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>

Field::Field(QObject *parent) Q_DECL_NOEXCEPT
	: QObject{ parent }
{
	qRegisterMetaType<Size>("Size");
	qRegisterMetaType<Component>("Component");
}

Field::~Field() Q_DECL_NOEXCEPT
{
	for (const auto& s : _field) {
		qDebug() << s;
	}
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

void Field::swap(const int x1, const int y1, const int x2, const int y2)
{
	qSwap(*(_field[y1 / 10].data() + (x1 / 10)),
		*(_field[y2 / 10].data() + (x2 / 10)));
}
