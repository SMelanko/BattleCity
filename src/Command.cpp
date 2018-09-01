#include "include/Command.h"

MoveLeftCommand::MoveLeftCommand(TankShPtr tank) Q_DECL_NOEXCEPT
	: _tank{ tank }
{
}

void MoveLeftCommand::execute() Q_DECL_NOEXCEPT
{
	// If direction was changed - just rotate the tank, else - move it.
	if (!_tank->setDirection(Tank::LEFT)) {
		_tank->move(-_tank->velocity(), 0);
	}
}

MoveUpCommand::MoveUpCommand(TankShPtr tank) Q_DECL_NOEXCEPT
	: _tank{ tank }
{
}

void MoveUpCommand::execute() Q_DECL_NOEXCEPT
{
	// If direction was changed - just rotate the tank, else - move it.
	if (!_tank->setDirection(Tank::UP)) {
		_tank->move(0, -_tank->velocity());
	}
}

MoveRightCommand::MoveRightCommand(TankShPtr tank) Q_DECL_NOEXCEPT
	: _tank{ tank }
{
}

void MoveRightCommand::execute() Q_DECL_NOEXCEPT
{
	// If direction was changed - just rotate the tank, else - move it.
	if (!_tank->setDirection(Tank::RIGHT)) {
		_tank->move(_tank->velocity(), 0);
	}
}

MoveDownCommand::MoveDownCommand(TankShPtr tank) Q_DECL_NOEXCEPT
	: _tank{ tank }
{
}

void MoveDownCommand::execute() Q_DECL_NOEXCEPT
{
	// If direction was changed - just rotate the tank, else - move it.
	if (!_tank->setDirection(Tank::DOWN)) {
		_tank->move(0, _tank->velocity());
	}
}

ShotCommand::ShotCommand(TankShPtr tank, ShellList& shellList) Q_DECL_NOEXCEPT
	: _tank{ tank }
	, _shellList{ shellList }
{
}

void ShotCommand::execute() Q_DECL_NOEXCEPT
{
	auto shell = _tank->shot();
	if (shell) {
		_shellList.add(shell);
	}
}

void NoCommand::execute() Q_DECL_NOEXCEPT
{
}
