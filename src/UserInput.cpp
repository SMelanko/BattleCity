#include "include/Command.h"
#include "include/UserInput.h"

UserInput::UserInput(QObject *parent) Q_DECL_NOEXCEPT
	: QObject{ parent }
{
}

void UserInput::OnReceive(CommandShPtr cmd)
{
	std::lock_guard<std::mutex> l{ _mut };
	_cmds.push(cmd);
}

CommandShPtr UserInput::Process()
{
	CommandShPtr cmd = Q_NULLPTR;

	{
		std::lock_guard<std::mutex> l{ _mut };
		if (!_cmds.empty()) {
			cmd = _cmds.front();
			_cmds.pop();
		}
	}

	if (!cmd) {
		cmd = std::make_shared<NoCommand>();
	}

	return cmd;
}
