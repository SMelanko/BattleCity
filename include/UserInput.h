#ifndef _BATTLECITY_USERINPUT_H_
#define _BATTLECITY_USERINPUT_H_

#include "include/command/Command.h"

#include <QObject>

#include <mutex>
#include <queue>

///
/// The UserInput class.
///

class UserInput : public QObject
{
	Q_OBJECT

public:
	/// Constructor.
	explicit UserInput(QObject *parent = Q_NULLPTR) Q_DECL_NOEXCEPT;

public:
	/// Processes user input info - sequence of keyboard keys.
	CommandShPtr Process();

public slots:
	/// Receives command that has been entered.
	void OnReceive(CommandShPtr cmd);

private:
	/// Command list.
	std::queue<CommandShPtr> _cmds;
	/// Object provides exclusive access to command list.
	std::mutex _mut;
};

#endif // _BATTLECITY_USERINPUT_H_
