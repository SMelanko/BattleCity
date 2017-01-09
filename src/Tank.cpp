#include "include/Clock.h"
#include "include/Tank.h"

#include <QQmlContext>

Tank::Tank(QObject *parent) Q_DECL_NOEXCEPT
	: QObject{ parent }
{
	registerType();
}

Tank::Tank(const Coordinates& coord, const Direction direct, const Health health,
	const Lives lives, const Armor arm, const ReloadingTime rt, const Velocity vel,
	const BodyImg& body, QObject *parent) Q_DECL_NOEXCEPT
	: QObject{ parent }
	, _coord{ coord }
	, _direct{ direct }
	, _health{ health }
	, _lives{ lives }
	, _arm{ arm }
	, _rt{ rt }
	, _vel{ vel }
	, _body{ body }
{
	registerType();
}

void Tank::move(const int x, const int y)
{
	if (x != 0) {
		_coord.setX(_coord.x() + x);
	}

	if (y != 0) {
		_coord.setY(_coord.y() + y);
	}

	_flagMove = true;
}

void Tank::shot()
{
	// For the first shot we should assign time point from past to make a shot.
	static auto lastShotTime = Clock<>::now() - std::chrono::milliseconds{ 500 };

	if (Clock<>::duration(lastShotTime, Clock<>::now()) > _rt) {
		qDebug() << QStringLiteral("Tank::shot()");
		lastShotTime = Clock<>::now();
	}
}

void Tank::render()
{
	if (_flagDirection) {
		Q_EMIT directionChanged(_direct);
		_flagDirection = false;
	}

	if (_flagMove) {
		Q_EMIT coordinatesChanged(_coord);
		_flagMove = false;
	}
}

void Tank::registerType()
{
	qRegisterMetaType<Coordinates>("Coordinates");
	qRegisterMetaType<Direction>("Direction");
	qRegisterMetaType<BodyImg>("BodyImg");
}
