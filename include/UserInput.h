#ifndef _BATTLECITY_USERINPUT_H_
#define _BATTLECITY_USERINPUT_H_

#include "include/Command.h"

#include <QObject>

#include <array>

///
/// The UserInput class.
///

class UserInput : public QObject
{
	Q_OBJECT

public:
	/// Type alias.
	using CommandArray = std::array<CommandShPtr, 2>;

public:
	/// Constructor.
	explicit UserInput(QObject *parent = Q_NULLPTR) Q_DECL_NOEXCEPT;

public:
	/// Processes user input info - sequence of keyboard keys.
	CommandArray process();

public slots:
	/// Receives command that has been entered.
	void onSetMoveCommand(CommandShPtr cmd);
	void onSetShotCommand(CommandShPtr cmd);
	void onRemoveMoveCommand();
	void onRemoveShotCommand();

private:
	/// Command queue.
	CommandArray _cmds;
};

#endif // _BATTLECITY_USERINPUT_H_
