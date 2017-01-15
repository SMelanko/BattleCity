#include "include/Clock.h"
#include "include/Field.h"
#include "include/Tank.h"

#include <QQmlContext>

Tank::Tank(QObject *parent) Q_DECL_NOEXCEPT
	: QObject{ parent }
{
	registerType();
}

Tank::Tank(FieldShPtr field, const Coordinates& coord, const Direction direct,
	const Health health, const Lives lives, const Armor arm,
	const ReloadingTime rt, const Velocity vel, const BodyImg& body,
	QObject *parent) Q_DECL_NOEXCEPT
	: QObject{ parent }
	, _field{ field }
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
	static auto checkFieldBorders = [](int& coord) -> bool {
		if (coord < 0) {
			coord = 0;
			return false;
		}
		if (coord > 360) {
			coord = 360;
			return false;
		}

		return true;
	};

	static auto checkFieldComponents = [this](int coord) -> bool {
		constexpr int tsz = 29;

		if (_direct == LEFT) {
			const auto y = _coord.y();
			auto item1 = _field->item(y / _vel, coord / _vel);
			auto item2 = _field->item((y + tsz) / _vel, coord / _vel);
			if (item1 == '0' || item1 == '1' || item1 == '4' ||
				item2 == '0' || item2 == '1' || item2 == '4') {
				return false;
			}
		} else if (_direct == UP) {
			const auto x = _coord.x();
			auto item1 = _field->item(coord / _vel, x / _vel);
			auto item2 = _field->item(coord / _vel, (x + tsz) / _vel);
			if (item1 == '0' || item1 == '1' || item1 == '4' ||
				item2 == '0' || item2 == '1' || item2 == '4') {
				return false;
			}
		} else if (_direct == RIGHT) {
			const auto y = _coord.y();
			auto item1 = _field->item(y / _vel, (coord + tsz) / _vel);
			auto item2 = _field->item((y + tsz) / _vel, (coord + tsz) / _vel);
			if (item1 == '0' || item1 == '1' || item1 == '4' ||
				item2 == '0' || item2 == '1' || item2 == '4') {
				return false;
			}
		} else if (_direct == DOWN) {
			const auto x = _coord.x();
			auto item1 = _field->item((coord + tsz) / _vel, x / _vel);
			auto item2 = _field->item((coord + tsz) / _vel, (x + tsz) / _vel);
			if (item1 == '0' || item1 == '1' || item1 == '4' ||
				item2 == '0' || item2 == '1' || item2 == '4') {
				return false;
			}
		}

		return true;
	};

	if (x != 0) {
		auto newX = _coord.x() + x;
		if (checkFieldBorders(newX) && checkFieldComponents(newX)) {
			_coord.setX(newX);
			_flagMove = true;
		}
	}

	if (y != 0) {
		auto newY = _coord.y() + y;
		if (checkFieldBorders(newY) && checkFieldComponents(newY)) {
			_coord.setY(newY);
			_flagMove = true;
		}
	}
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

UserTank::UserTank(FieldShPtr field, const Tank::Coordinates& coord,
	const Tank::Direction direct, const Tank::Health health,
	const Tank::Lives lives, const Tank::Armor arm, const Tank::ReloadingTime rt,
	const Tank::Velocity vel, const Tank::BodyImg& body,
	QObject* parent) Q_DECL_NOEXCEPT
	: Tank{ field, coord, direct, health, lives, arm, rt, vel, body, parent }
{
}
