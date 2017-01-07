#ifndef _BATTLECITY_COMMAND_H_
#define _BATTLECITY_COMMAND_H_

#include "include/Tank.h"

#include <memory>

///
/// The Command class.
///

class Command
{
public:
	/// Destructor.
	virtual ~Command() Q_DECL_NOEXCEPT = default;

public:
	/// Executes action.
	virtual void execute() Q_DECL_NOEXCEPT = 0;
};

/// Command type alias.
using CommandShPtr = std::shared_ptr<Command>;

///
/// The MoveLeftCommand class.
///

class MoveLeftCommand : public Command
{
public:
	/// Constructor.
	explicit MoveLeftCommand(TankShPtr tank) Q_DECL_NOEXCEPT;

public:
	/// Executes moving left.
	void execute() Q_DECL_NOEXCEPT Q_DECL_OVERRIDE;

private:
	/// Instance of the user tank.
	TankShPtr _tank;
};

///
/// The MoveUpCommand class.
///

class MoveUpCommand : public Command
{
public:
	/// Constructor.
	explicit MoveUpCommand(TankShPtr tank) Q_DECL_NOEXCEPT;

public:
	/// Executes moving up.
	void execute() Q_DECL_NOEXCEPT Q_DECL_OVERRIDE;

private:
	/// Instance of the user tank.
	TankShPtr _tank;
};

///
/// The MoveRightCommand class.
///

class MoveRightCommand : public Command
{
public:
	/// Constructor.
	explicit MoveRightCommand(TankShPtr tank) Q_DECL_NOEXCEPT;

public:
	/// Executes moving right.
	void execute() Q_DECL_NOEXCEPT Q_DECL_OVERRIDE;

private:
	/// Instance of the user tank.
	TankShPtr _tank;
};

///
/// The MoveDownCommand class.
///

class MoveDownCommand : public Command
{
public:
	/// Constructor.
	explicit MoveDownCommand(TankShPtr tank) Q_DECL_NOEXCEPT;

public:
	/// Executes moving down.
	void execute() Q_DECL_NOEXCEPT Q_DECL_OVERRIDE;

private:
	/// Instance of the user tank.
	TankShPtr _tank;
};

///
/// The ShotCommand class.
///

class ShotCommand : public Command
{
public:
	/// Constructor.
	explicit ShotCommand(TankShPtr tank) Q_DECL_NOEXCEPT;

public:
	/// Executes tank's shot.
	void execute() Q_DECL_NOEXCEPT Q_DECL_OVERRIDE;

private:
	/// Instance of the user tank.
	TankShPtr _tank;
};

///
/// The NoCommand class.
///

class NoCommand : public Command
{
public:
	/// Executes nothing.
	void execute() Q_DECL_NOEXCEPT Q_DECL_OVERRIDE;
};

#endif // _BATTLECITY_COMMAND_H_
