#include "include/Tank.h"

#include <QQmlContext>

Tank::Tank(QObject *parent) Q_DECL_NOEXCEPT
	: QObject{ parent }
{
	registerType();
}

Tank::Tank(const Coordinates& coord, const Direction direct, const Health health,
	const Armor arm, const FireRate fr, const Velocity vel, const BodyImg& body,
	QObject *parent) Q_DECL_NOEXCEPT
	: QObject{ parent }
	, _coord{ coord }
	, _direct{ direct }
	, _health{ health }
	, _arm{ arm }
	, _fr{ fr }
	, _vel{ vel }
	, _body{ body }
{
	registerType();
}

void Tank::Move(const int x, const int y)
{
	if (x != 0) {
		_coord.setX(_coord.x() + x);
	}

	if (y != 0) {
		_coord.setY(_coord.y() + y);
	}

	Q_EMIT coordinatesChanged(_coord);
}

void Tank::Shot()
{
}

void Tank::registerType()
{
	qRegisterMetaType<Coordinates>("Coordinates");
	qRegisterMetaType<Direction>("Direction");
	qRegisterMetaType<BodyImg>("BodyImg");
}
