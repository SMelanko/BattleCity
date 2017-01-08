#include "INCLUDE/TankFactory.h"

TankShPtr UserTankFactory::create() const
{
	Tank::Coordinates coord = { 10, 10 };
	Tank::Direction direct = Tank::UP;
	Tank::Health health = 100;
	Tank::Lives lives = 3;
	Tank::Armor arm = 100;
	Tank::FireRate fr = 1;
	Tank::Velocity vel = 10;
	Tank::BodyImg body = QLatin1String{ "../img/tank-user.png" };

	return std::make_shared<Tank>(coord, direct, health, lives, arm, fr, vel, body);
}
