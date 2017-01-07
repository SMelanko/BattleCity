#ifndef _BATTLECITY_USERINPUT_H_
#define _BATTLECITY_USERINPUT_H_

#include "include/Command.h"

#include <QObject>

#include <queue>

///
/// The UserInput class.
///

class UserInput : public QObject
{
	Q_OBJECT

public:
	/// Type alias.
	using CommandQueue = std::queue<CommandShPtr>;

public:
	/// Constructor.
	explicit UserInput(QObject *parent = Q_NULLPTR) Q_DECL_NOEXCEPT;

public:
	/// Processes user input info - sequence of keyboard keys.
	CommandShPtr process();

public slots:
	/// Receives command that has been entered.
	void onReceive(CommandShPtr cmd);

private:
	/// Command queue.
	CommandQueue _cmds;
};

#endif // _BATTLECITY_USERINPUT_H_
