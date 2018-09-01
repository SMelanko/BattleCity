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

	map();
}

void Tank::map()
{
	for (int x = 0; x < 3; ++x) {
		for (int y = 0; y < 3; ++y) {
			_field->setItem(_coord.x() + (x * 10), _coord.y() + (y * 10),
				QLatin1Char{ 'u' });
		}
	}
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

	if (_flagMove) {
		if (_direct == LEFT) {
			for (int i = 0; i < 3; ++i) {
				_field->swap(_coord.x(), _coord.y() + (i * 10),
					_coord.x() + 30, _coord.y() + (i * 10));
			}
		} else if (_direct == RIGHT) {
			for (int i = 0; i < 3; ++i) {
				_field->swap(_coord.x() - 10, _coord.y() + (i * 10),
					_coord.x() + 20, _coord.y() + (i * 10));
			}
		} else if (_direct == UP) {
			for (int i = 0; i < 3; ++i) {
				_field->swap(_coord.x() + (i * 10), _coord.y(),
					_coord.x() + (i * 10), _coord.y() + 30);
			}
		} else if (_direct == DOWN) {
			for (int i = 0; i < 3; ++i) {
				_field->swap(_coord.x() + (i * 10), _coord.y() - 10,
					_coord.x() + (i * 10), _coord.y() + 20);
			}
		}
	}
}

ShellShPtr Tank::shot()
{
	// For the first shot we should assign time point from the past to make a shot.
	static auto lastShotTime = Clock<>::now() - std::chrono::milliseconds{ 500 };

	ShellShPtr shell = nullptr;

	if (Clock<>::duration(lastShotTime, Clock<>::now()) > _rt) {
		if (_direct == LEFT) {
			shell = createShell(-10, 10);
		} else if (_direct == UP) {
			shell = createShell(10, -10);
		} else if (_direct == RIGHT) {
			shell = createShell(30, 10);
		} else if (_direct == DOWN) {
			shell = createShell(10, 30);
		}

		lastShotTime = Clock<>::now();
	}

	return shell;
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

WeakEnemyTank::WeakEnemyTank(FieldShPtr field, const Tank::Coordinates& coord,
	const Tank::Direction direct, const Tank::Health health,
	const Tank::Lives lives, const Tank::Armor arm, const Tank::ReloadingTime rt,
	const Tank::Velocity vel, const Tank::BodyImg& body,
	QObject* parent) Q_DECL_NOEXCEPT
	: Tank{ field, coord, direct, health, lives, arm, rt, vel, body, parent }
{
}

FastEnemyTank::FastEnemyTank(FieldShPtr field, const Tank::Coordinates& coord,
	const Tank::Direction direct, const Tank::Health health,
	const Tank::Lives lives, const Tank::Armor arm, const Tank::ReloadingTime rt,
	const Tank::Velocity vel, const Tank::BodyImg& body,
	QObject* parent) Q_DECL_NOEXCEPT
	: Tank{ field, coord, direct, health, lives, arm, rt, vel, body, parent }
{
}

RapidFireEnemyTank::RapidFireEnemyTank(FieldShPtr field, const Tank::Coordinates& coord,
	const Tank::Direction direct, const Tank::Health health,
	const Tank::Lives lives, const Tank::Armor arm, const Tank::ReloadingTime rt,
	const Tank::Velocity vel, const Tank::BodyImg& body,
	QObject* parent) Q_DECL_NOEXCEPT
	: Tank{ field, coord, direct, health, lives, arm, rt, vel, body, parent }
{
}

ArmoredTank::ArmoredTank(FieldShPtr field, const Tank::Coordinates& coord,
	const Tank::Direction direct, const Tank::Health health,
	const Tank::Lives lives, const Tank::Armor arm, const Tank::ReloadingTime rt,
	const Tank::Velocity vel, const Tank::BodyImg& body,
	QObject* parent) Q_DECL_NOEXCEPT
	: Tank{ field, coord, direct, health, lives, arm, rt, vel, body, parent }
{
}
