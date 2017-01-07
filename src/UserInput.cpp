#include "include/Command.h"
#include "include/UserInput.h"

UserInput::UserInput(QObject *parent) Q_DECL_NOEXCEPT
	: QObject{ parent }
{
}

void UserInput::onReceive(CommandShPtr cmd)
{
	_cmds.push(cmd);
}

CommandShPtr UserInput::process()
{
	CommandShPtr cmd = Q_NULLPTR;

	if (!_cmds.empty()) {
		cmd = _cmds.front();
		_cmds.pop();
	}

	return (cmd) ? cmd : std::make_shared<NoCommand>();
}
