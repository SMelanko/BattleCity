#include "include/Clock.h"
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
	static auto checkFieldBorders = [](const int coord) noexcept -> bool {
		return (0 <= coord && coord <= 360) ? true : false;
	};

	static auto isObstacle = [](const QChar& item) {
		return (item == QLatin1Char('0') || item == QLatin1Char('1') ||
			item == QLatin1Char('4')) ? false : true;
	};

	static auto checkFieldComponents = [this](int coord) -> bool {
		constexpr int tsz = 29;
		Field::Component left, right;

		if (_direct == LEFT) {
			const auto y = _coord.y();
			left = _field->item1(coord, (y + tsz));
			right = _field->item1(coord, y);
		} else if (_direct == UP) {
			const auto x = _coord.x();
			left = _field->item1(x, coord);
			right = _field->item1((x + tsz), coord);
		} else if (_direct == RIGHT) {
			const auto y = _coord.y();
			left = _field->item1((coord + tsz), y);
			right = _field->item1((coord + tsz), (y + tsz));
		} else if (_direct == DOWN) {
			const auto x = _coord.x();
			left = _field->item1((x + tsz), (coord + tsz));
			right = _field->item1(x, (coord + tsz));
		}

		return (isObstacle(left) && isObstacle(right));;
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
	// For the first shot we should assign time point from the past to make a shot.
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
