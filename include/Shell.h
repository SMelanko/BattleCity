#ifndef _BATTLECITY_SHELL_H_
#define _BATTLECITY_SHELL_H_

#include "include/Field.h"

#include <QObject>
#include <QPoint>

#include <memory>

class FlyableObject : public QObject
{
	Q_OBJECT

	Q_PROPERTY(Coordinates coord READ coordinates WRITE setCoordinates NOTIFY coordinatesChanged)
	Q_PROPERTY(Direction direct READ direction WRITE setDirection NOTIFY directionChanged)
	Q_PROPERTY(Speed speed READ speed WRITE setSpeed NOTIFY speedChanged)

public:
	/// Type alias.
	using Coordinates = QPoint;
	using Speed = uint16_t;

public:
	/// The Direction enum.
	enum Direction
	{
		LEFT,
		UP,
		RIGHT,
		DOWN,
		NONE
	};
	Q_ENUM(Direction)

public:
	/// Constructor.
	FlyableObject(const Coordinates& coord, const Direction direct,
		const Speed speed, QObject *parent = Q_NULLPTR) Q_DECL_NOEXCEPT;
	/// Destructor.
	virtual ~FlyableObject() Q_DECL_NOEXCEPT = default;

public:
	/// Moves object.
	virtual void move(const int x, const int y) = 0;

	/// Returns object's coordinates.
	Coordinates coordinates() const Q_DECL_NOEXCEPT;
	/// Returns object's direction.
	Direction direction() const Q_DECL_NOEXCEPT;
	/// Returns object's speed value.
	Speed speed() const Q_DECL_NOEXCEPT;

	/// Sets new object coordinates.
	void setCoordinates(const Coordinates& coord);
	/// Sets new object direction.
	bool setDirection(const Direction direct);
	/// Sets new object speed value.
	void setSpeed(const Speed speed);

Q_SIGNALS:
	/// Object's coordinates was changed.
	void coordinatesChanged(const Coordinates newCoord);
	/// Object's direction was changed.
	void directionChanged(const Direction newDirect);
	/// Object's speed value was changed.
	void speedChanged();

protected:
	/// Render flags.
	bool _flagDirection;
	bool _flagMove;

private:
	/// Object's coordinates of the upper left corner.
	Coordinates _coord;
	/// Object's direction for moving.
	Direction _direct;
	/// Object's speed - pixels per step.
	Speed _speed;
};

///
/// Inline implementation of the Tank class methods.
///

inline FlyableObject::Coordinates FlyableObject::coordinates() const Q_DECL_NOEXCEPT
{
	return _coord;
}

inline FlyableObject::Direction FlyableObject::direction() const Q_DECL_NOEXCEPT
{
	return _direct;
}

inline FlyableObject::Speed FlyableObject::speed() const Q_DECL_NOEXCEPT
{
	return _speed;
}

inline void FlyableObject::setCoordinates(const FlyableObject::Coordinates& coord)
{
	_coord = coord;
}

inline bool FlyableObject::setDirection(const FlyableObject::Direction direct)
{
	if (_direct != direct) {
		_direct = direct;

		_flagDirection = true;
	}

	return _flagDirection;
}

inline void FlyableObject::setSpeed(const FlyableObject::Speed speed)
{
	_speed = speed;
}

///
/// The Shell class.
///

class Shell : public FlyableObject
{
	Q_OBJECT

public:
	/// Shell state.
	enum State
	{
		CREATE,
		MOVE,
		EXPLODE
	};
	Q_ENUM(State)

public:
	/// Constructor.
	Shell(FieldShPtr field, const Coordinates& coord,
		const Direction direct, const Speed speed = 20,
		QObject *parent = Q_NULLPTR) Q_DECL_NOEXCEPT;

public:
	void move() Q_DECL_OVERRIDE
	{
		static auto checkFieldBorders = [](const int coord) noexcept -> bool {
			return (0 <= coord && coord <= 380) ? true : false;
		};

		static auto isObstacle = [](const QChar& item) {
			return (item == QLatin1Char('0') || item == QLatin1Char('1') ||
				item == QLatin1Char('4')) ? false : true;
		};

		static auto checkFieldComponents = [this](int coord) -> bool {
			constexpr int tsz = 9;
			Field::Component left;
			const auto direct = direction();

			if (direct == LEFT) {
				left = _field->item1(coord, coordinates().y());
			} else if (direct == UP) {
				left = _field->item1(coordinates().x(), coord);
			} else if (direct == RIGHT) {
				left = _field->item1((coord + tsz), coordinates().y());
			} else if (direct == DOWN) {
				left = _field->item1((coordinates().x() + tsz), (coord + tsz));
			}

			return isObstacle(left);
		};

		const auto direct = direction();
		int del = 0;
		if (direct == FlyableObject::LEFT) {
			del = -20;
		} else if (direct == FlyableObject::RIGHT) {
			del = 20;
		} else if (direct == FlyableObject::UP) {
			del = -20;
		} else if (direct == FlyableObject::DOWN) {
			del = 20;
		}

		if (direct == FlyableObject::LEFT || direct == FlyableObject::RIGHT) {
			auto newX = coordinates().x() + del;
			if (checkFieldBorders(newX) && checkFieldComponents(newX)) {
				setCoordinates({ newX, 0 });
				_state = MOVE;
			} else {
				_state = EXPLODE;
			}
		}

		if (direct == FlyableObject::UP || direct == FlyableObject::DOWN) {
			auto newY = coordinates().y() + del;
			if (checkFieldBorders(newY) && checkFieldComponents(newY)) {
				setCoordinates({ 0, newY });
				_state = MOVE;
			} else {
				_state = EXPLODE;
			}
		}
	}

	State state() Q_DECL_NOEXCEPT
	{
		return _state;
	}

private:
	/// Pointer to the field.
	FieldShPtr _field;
	/// Shell state.
	State _state;
};

/// Shell alias.
using ShellShPtr = std::shared_ptr<Shell>;

///
/// The ShellList class.
///

class ShellList : public QObject
{
	Q_OBJECT

public:
	/// Constructor.
	ShellList() Q_DECL_NOEXCEPT = default;

public:
	/// Adds new one to the list.
	void add(ShellShPtr shell)
	{
		_shells.append(shell);
	}
	/// Removes shell from the list.
	void remove(const int index)
	{
		_shells.removeAt(index);
	}
	/// Renders shells.
	void render()
	{
		for (decltype(_shells.size()) i = 0; i < _shells.size(); ++i) {
			const auto coords = _shells[i]->coordinates();
			Q_EMIT move(i, coords.x(), coords.y());
		}
	}

	/// Updates list.
	void update()
	{
		for (auto& shell : _shells) {
			shell->move();
		}
	}

Q_SIGNALS:
	/// Draw shell on the field.
	void create(const int x, const int y);
	/// Moves a shell to the new coordinates.
	void move(const int index, const int x, const int y);

private:
	/// Shell list.
	QList<ShellShPtr> _shells;
}

#endif // _BATTLECITY_SHELL_H_
