#ifndef _BATTLECITY_TANK_H_
#define _BATTLECITY_TANK_H_

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
	Q_PROPERTY(Armor armor READ armor WRITE setArmor NOTIFY armorChanged)
	Q_PROPERTY(FireRate fireRate READ fireRate WRITE setFireRate NOTIFY fireRateChanged)
	Q_PROPERTY(Velocity velocity READ velocity WRITE setVelocity NOTIFY velocityChanged)
	Q_PROPERTY(BodyImg body READ bodyImg WRITE setBodyImg NOTIFY bodyImgChanged)

public:
	/// Type alias.
	using Coordinates = QPoint;
	using Health = uint16_t;
	using Armor = uint16_t;
	using FireRate = uint16_t;
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
	Tank(const Coordinates& coord, const Direction direct, const Health health,
		const Armor arm, const FireRate fr, const Velocity vel,
		const BodyImg& body, QObject *parent = Q_NULLPTR) Q_DECL_NOEXCEPT;

public:
	/// Moves tank.
	void Move(const int x, const int y);
	/// Makes a shot.
	void Shot();

	/// Returns tank's coordinates.
	Coordinates coordinates() const Q_DECL_NOEXCEPT;
	/// Returns tank's direction.
	Direction direction() const Q_DECL_NOEXCEPT;
	/// Returns tank's health value.
	Health health() const Q_DECL_NOEXCEPT;
	/// Returns tank's armor value.
	Armor armor() const Q_DECL_NOEXCEPT;
	/// Returns tank's fire rate value.
	FireRate fireRate() const Q_DECL_NOEXCEPT;
	/// Returns tank's velocity value.
	Velocity velocity() const Q_DECL_NOEXCEPT;
	/// Returns tank's body image.
	BodyImg bodyImg() const Q_DECL_NOEXCEPT;

	/// Sets new tank coordinates.
	void setCoordinates(const Coordinates& coord);
	/// Sets new tank direction.
	void setDirection(const Direction direct);
	/// Sets new tank health value.
	void setHealth(const Health health);
	/// Sets new tank armor value.
	void setArmor(const Armor arm);
	/// Sets new tank fire rate value.
	void setFireRate(const FireRate fr);
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
	/// Tank's armor value was changed.
	void armorChanged();
	/// Tank's fire rate value was changed.
	void fireRateChanged();
	/// Tank's velocity value was changed.
	void velocityChanged();
	/// Tank's body image was changed.
	void bodyImgChanged();

private:
	/// Registers the type name.
	void registerType();

private:
	/// Tank's coordinates.
	Coordinates _coord;
	/// Tank's direction.
	Direction _direct;
	/// Tank's "health".
	Health _health;
	/// Tank's armor.
	Armor _arm ;
	/// Tank's fire rate - shots per second.
	FireRate _fr;
	/// Tank's velocity - pixels per step.
	Velocity _vel;
	/// Tank's body image.
	BodyImg _body;
};

/// Tank type alias.
using TankShPtr = std::shared_ptr<Tank>;

///
/// Inline implementation of the Tank class methods.
///

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

inline Tank::Armor Tank::armor() const Q_DECL_NOEXCEPT
{
	return _arm;
}

inline Tank::FireRate Tank::fireRate() const Q_DECL_NOEXCEPT
{
	return _fr;
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

inline void Tank::setDirection(const Tank::Direction direct)
{
	if (_direct != direct) {
		_direct = direct;

		Q_EMIT directionChanged(_direct);
	}
}

inline void Tank::setHealth(const Tank::Health health)
{
	_health = health;
}

inline void Tank::setArmor(const Tank::Armor arm)
{
	_arm = arm;
}

inline void Tank::setFireRate(const Tank::FireRate fr)
{
	_fr = fr;
}

inline void Tank::setVelocity(const Tank::Velocity vel)
{
	_vel = vel;
}

inline void Tank::setBodyImg(const Tank::BodyImg& body)
{
	_body = body;
}

#endif // _BATTLECITY_TANK_H_
