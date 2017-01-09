#include "include/Command.h"
#include "include/UserInput.h"

UserInput::UserInput(QObject *parent) Q_DECL_NOEXCEPT
	: QObject{ parent }
{
}

void UserInput::onRemoveMoveCommand()
{
	if (_cmds[0]) {
		_cmds[0].reset();
	}
}

void UserInput::onRemoveShotCommand()
{
	if (_cmds[1]) {
		_cmds[1].reset();
	}
}

void UserInput::onSetMoveCommand(CommandShPtr cmd)
{
	_cmds[0] = cmd;
}

void UserInput::onSetShotCommand(CommandShPtr cmd)
{
	_cmds[1] = cmd;
}

UserInput::CommandArray UserInput::process()
{
	return _cmds;
}
