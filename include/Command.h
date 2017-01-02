#ifndef _BATTLECITY_COMMAND_H_
#define _BATTLECITY_COMMAND_H_

#include <memory>

///
/// The Command class.
///

class Command
{
public:
	virtual ~Command() noexcept = default;

public:
	/// Executes action.
	virtual void Execute() noexcept = 0;
};

using CommandUnPtr = std::unique_ptr<Command>;
using CommandShPtr = std::shared_ptr<Command>;

///
/// The MoveLeftCommand class.
///

class MoveLeftCommand : public Command
{
public:
	/// Executes moving left.
	void Execute() noexcept override;
};

///
/// The MoveUpCommand class.
///

class MoveUpCommand : public Command
{
public:
	/// Executes moving up.
	void Execute() noexcept override;
};

///
/// The MoveRightCommand class.
///

class MoveRightCommand : public Command
{
public:
	/// Executes moving right.
	void Execute() noexcept override;
};

///
/// The MoveDownCommand class.
///

class MoveDownCommand : public Command
{
public:
	/// Executes moving down.
	void Execute() noexcept override;
};

///
/// The ShotCommand class.
///

class ShotCommand : public Command
{
public:
	/// Executes tank's shot.
	void Execute() noexcept override;
};

///
/// The NoCommand class.
///

class NoCommand : public Command
{
public:
	/// Executes nothing.
	void Execute() noexcept override;
};

///
/// The PauseCommand class.
///

class PauseCommand : public Command
{
public:
	/// Executes pause in the game.
	void Execute() noexcept override;
};

#endif // _BATTLECITY_COMMAND_H_
