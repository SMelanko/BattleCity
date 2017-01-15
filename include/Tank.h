#ifndef _BATTLECITY_TANK_H_
#define _BATTLECITY_TANK_H_

#include "include/Field.h"

#include <QDebug>
#include <QObject>
#include <QPoint>

#include <memory>

///
/// The Tank class.
///

class Tank : public QObject
{
	Q_OBJECT

	Q_PROPERTY(Coordinates coord READ coordinates WRITE setCoordinates NOTIFY coordinatesChanged)
	Q_PROPERTY(Direction direct READ direction WRITE setDirection NOTIFY directionChanged)
	Q_PROPERTY(Health health READ health WRITE setHealth NOTIFY healthChanged)
	Q_PROPERTY(Lives lives READ lives WRITE setLives NOTIFY livesChanged)
	Q_PROPERTY(Armor armor READ armor WRITE setArmor NOTIFY armorChanged)
	Q_PROPERTY(ReloadingTime reloadingTime READ reloadingTime WRITE setReloadingTime NOTIFY reloadingTimeChanged)
	Q_PROPERTY(Velocity velocity READ velocity WRITE setVelocity NOTIFY velocityChanged)
	Q_PROPERTY(BodyImg body READ bodyImg WRITE setBodyImg NOTIFY bodyImgChanged)

public:
	/// Type alias.
	using Coordinates = QPoint;
	using Health = uint16_t;
	using Lives = uint16_t;
	using Armor = uint16_t;
	using ReloadingTime = double;
	using Velocity = uint16_t;
	using BodyImg = QString;

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
	explicit Tank(QObject *parent = Q_NULLPTR) Q_DECL_NOEXCEPT;
	/// Constructor.
	Tank(FieldShPtr field, const Coordinates& coord, const Direction direct,
		const Health health, const Lives lives, const Armor arm,
		const ReloadingTime rt, const Velocity vel, const BodyImg& body,
		QObject *parent = Q_NULLPTR) Q_DECL_NOEXCEPT;
	/// Destructor.
	virtual ~Tank() Q_DECL_NOEXCEPT = default;

public:
	/// Tank's death.
	void explosion() Q_DECL_NOEXCEPT;
	/// Returns true if tank is alive.
	bool isAlive() const Q_DECL_NOEXCEPT;
	/// Moves tank.
	void move(const int x, const int y);
	/// Makes a shot.
	void shot();

	/// Makes tank rendering.
	void render();

	/// Returns tank's coordinates.
	Coordinates coordinates() const Q_DECL_NOEXCEPT;
	/// Returns tank's direction.
	Direction direction() const Q_DECL_NOEXCEPT;
	/// Returns tank's health value.
	Health health() const Q_DECL_NOEXCEPT;
	/// Returns tank's lives value.
	Lives lives() const Q_DECL_NOEXCEPT;
	/// Returns tank's armor value.
	Armor armor() const Q_DECL_NOEXCEPT;
	/// Returns tank's reloading time value.
	ReloadingTime reloadingTime() const Q_DECL_NOEXCEPT;
	/// Returns tank's velocity value.
	Velocity velocity() const Q_DECL_NOEXCEPT;
	/// Returns tank's body image.
	BodyImg bodyImg() const Q_DECL_NOEXCEPT;

	/// Sets new tank coordinates.
	void setCoordinates(const Coordinates& coord);
	/// Sets new tank direction.
	bool setDirection(const Direction direct);
	/// Sets new tank health value.
	void setHealth(const Health health);
	/// Sets new tank lives value.
	void setLives(const Lives lives);
	/// Sets new tank armor value.
	void setArmor(const Armor arm);
	/// Sets new tank reloading time value.
	void setReloadingTime(const ReloadingTime rt);
	/// Sets new tank velocity value.
	void setVelocity(const Velocity vel);
	/// Sets new tank body image.
	void setBodyImg(const BodyImg& body);

Q_SIGNALS:
	/// Tank's coordinates was changed.
	void coordinatesChanged(const Coordinates newCoord);
	/// Tank's direction was changed.
	void directionChanged(const Direction newDirect);
	/// Tank's health value was changed.
	void healthChanged();
	/// Tank's lives value was changed.
	void livesChanged();
	/// Tank's armor value was changed.
	void armorChanged();
	/// Tank's reloading time value was changed.
	void reloadingTimeChanged();
	/// Tank's velocity value was changed.
	void velocityChanged();
	/// Tank's body image was changed.
	void bodyImgChanged();

private:
	/// Registers the type name.
	void registerType();

private:
	/// Pointer to the field.
	FieldShPtr _field;

	/// Tank's coordinates.
	Coordinates _coord;
	/// Tank's direction.
	Direction _direct;
	/// Tank's "health".
	Health _health;
	/// Tank's lives.
	Lives _lives;
	/// Tank's armor.
	Armor _arm ;
	/// Tank's reloading value - 1 shot per _rt (milliseconds).
	ReloadingTime _rt;
	/// Tank's velocity - pixels per step.
	Velocity _vel;
	/// Tank's body image.
	BodyImg _body;

	/// Render flags.
	bool _flagDirection;
	bool _flagMove;
};

/// Tank alias.
using TankShPtr = std::shared_ptr<Tank>;

///
/// Inline implementation of the Tank class methods.
///

inline void Tank::explosion() Q_DECL_NOEXCEPT
{
	setHealth(0);
	setLives(0);
}

inline bool Tank::isAlive() const Q_DECL_NOEXCEPT
{
	return lives() > 0 && health() > 0;
}

inline Tank::Coordinates Tank::coordinates() const Q_DECL_NOEXCEPT
{
	return _coord;
}

inline Tank::Direction Tank::direction() const Q_DECL_NOEXCEPT
{
	return _direct;
}

inline Tank::Health Tank::health() const Q_DECL_NOEXCEPT
{
	return _health;
}

inline Tank::Lives Tank::lives() const Q_DECL_NOEXCEPT
{
	return _lives;
}

inline Tank::Armor Tank::armor() const Q_DECL_NOEXCEPT
{
	return _arm;
}

inline Tank::ReloadingTime Tank::reloadingTime() const Q_DECL_NOEXCEPT
{
	return _rt;
}

inline Tank::Velocity Tank::velocity() const Q_DECL_NOEXCEPT
{
	return _vel;
}

inline Tank::BodyImg Tank::bodyImg() const Q_DECL_NOEXCEPT
{
	return _body;
}

inline void Tank::setCoordinates(const Tank::Coordinates& coord)
{
	_coord = coord;
}

inline bool Tank::setDirection(const Tank::Direction direct)
{
	if (_direct != direct) {
		_direct = direct;

		_flagDirection = true;
	}

	return _flagDirection;
}

inline void Tank::setHealth(const Tank::Health health)
{
	_health = health;
}

inline void Tank::setLives(const Lives lives)
{
	_lives = lives;
}

inline void Tank::setArmor(const Tank::Armor arm)
{
	_arm = arm;
}

inline void Tank::setReloadingTime(const Tank::ReloadingTime fr)
{
	_rt = fr;
}

inline void Tank::setVelocity(const Tank::Velocity vel)
{
	_vel = vel;
}

inline void Tank::setBodyImg(const Tank::BodyImg& body)
{
	_body = body;
}

namespace tdefs
{
	Q_DECL_CONSTEXPR Tank::Coordinates coord = { 120, 350 };
	Q_DECL_CONSTEXPR Tank::Direction direct = Tank::UP;
	Q_DECL_CONSTEXPR Tank::Health health = 100;
	Q_DECL_CONSTEXPR Tank::Lives lives = 3;
	Q_DECL_CONSTEXPR Tank::Armor arm = 100;
	Q_DECL_CONSTEXPR Tank::ReloadingTime rt = 500.0;
	Q_DECL_CONSTEXPR Tank::Velocity vel = 10;
} // namespace tdefs

///
/// The UserTank class.
///

class UserTank : public Tank
{
public:
	/// Constructor.
	UserTank(FieldShPtr field, const Coordinates& coord = tdefs::coord,
		const Direction direct = tdefs::direct, const Health health = tdefs::health,
		const Lives lives = tdefs::lives, const Armor arm = tdefs::arm,
		const ReloadingTime rt = tdefs::rt, const Velocity vel = tdefs::vel,
		const BodyImg& body = QStringLiteral("../img/tank-user.png"),
		QObject *parent = Q_NULLPTR) Q_DECL_NOEXCEPT;
};

#endif // _BATTLECITY_TANK_H_
