#ifndef _BATTLECITY_TANKFACTORY_H_
#define _BATTLECITY_TANKFACTORY_H_

#include "include/Tank.h"

///
/// The TankFactory class.
///

class TankFactory
{
public:
	/// Destructor.
	virtual ~TankFactory() noexcept = default;

public:
	/// Creates a new tank.
	virtual TankShPtr create() const = 0;
};

/// TankFactory alias.
using TankFactoryUnPtr = std::unique_ptr<TankFactory>;
using TankFactoryShPtr = std::unique_ptr<TankFactory>;

///
/// The UserTankFactory class.
///

class UserTankFactory : public TankFactory
{
public:
	/// Creates user tank.
	TankShPtr create() const override;
};

#endif // _BATTLECITY_TANKFACTORY_H_
