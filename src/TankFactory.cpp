#include "INCLUDE/TankFactory.h"

TankShPtr UserTankFactory::create() const
{
	Q_DECL_CONSTEXPR Tank::Coordinates coord = { 100, 100 };
	Q_DECL_CONSTEXPR Tank::Direction direct = Tank::UP;
	Q_DECL_CONSTEXPR Tank::Health health = 100;
	Q_DECL_CONSTEXPR Tank::Lives lives = 3;
	Q_DECL_CONSTEXPR Tank::Armor arm = 100;
	Q_DECL_CONSTEXPR Tank::ReloadingTime fr = 500.0;
	Q_DECL_CONSTEXPR Tank::Velocity vel = 10;
	Tank::BodyImg body = QStringLiteral("../img/tank-user.png");

	return std::make_shared<Tank>(coord, direct, health, lives, arm, fr, vel, body);
}
