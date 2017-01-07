#include "include/Command.h"

#include <QDebug>

MoveLeftCommand::MoveLeftCommand(TankShPtr tank) Q_DECL_NOEXCEPT
	: _tank{ tank }
{
}

void MoveLeftCommand::execute() Q_DECL_NOEXCEPT
{
	_tank->setDirection(Tank::LEFT);
	_tank->Move(-_tank->velocity(), 0);
}

MoveUpCommand::MoveUpCommand(TankShPtr tank) Q_DECL_NOEXCEPT
	: _tank{ tank }
{
}

void MoveUpCommand::execute() Q_DECL_NOEXCEPT
{
	_tank->setDirection(Tank::UP);
	_tank->Move(0, -_tank->velocity());
}

MoveRightCommand::MoveRightCommand(TankShPtr tank) Q_DECL_NOEXCEPT
	: _tank{ tank }
{
}

void MoveRightCommand::execute() Q_DECL_NOEXCEPT
{
	_tank->setDirection(Tank::RIGHT);
	_tank->Move(_tank->velocity(), 0);
}

MoveDownCommand::MoveDownCommand(TankShPtr tank) Q_DECL_NOEXCEPT
	: _tank{ tank }
{
}

void MoveDownCommand::execute() Q_DECL_NOEXCEPT
{
	_tank->setDirection(Tank::DOWN);
	_tank->Move(0, _tank->velocity());
}

ShotCommand::ShotCommand(TankShPtr tank) Q_DECL_NOEXCEPT
	: _tank{ tank }
{
}

void ShotCommand::execute() Q_DECL_NOEXCEPT
{
	qDebug() << QStringLiteral("ShotCommand::Execute");
}

void NoCommand::execute() Q_DECL_NOEXCEPT
{
}
