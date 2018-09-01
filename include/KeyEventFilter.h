#ifndef _BATTLECITY_KEYEVENTFILTER_H_
#define _BATTLECITY_KEYEVENTFILTER_H_

#include "include/Command.h"

#include <QObject>

#include <set>

QT_FORWARD_DECLARE_CLASS(QEvent)

///
/// The KeyEventFilter class.
///

class KeyEventFilter : public QObject
{
	Q_OBJECT

public:
	/// Type alias.
	using KeyCode = int;

public:
	/// Constructor.
	KeyEventFilter(TankShPtr userTank, ShellList& shellList,
		QObject *parent = Q_NULLPTR) Q_DECL_NOEXCEPT;

Q_SIGNALS:
	/// Emits command that has been entered.
	void setMoveCommand(CommandShPtr cmd);
	void setShotCommand(CommandShPtr cmd);
	void removeMoveCommand();
	void removeShotCommand();

protected:
	/// Handles key press events.
	bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;

private:
	/// Creates command according to pressed key.
	CommandShPtr makeCommand(const KeyCode key) const;

private:
	/// Instance of the user tank.
	TankShPtr _userTank;
	/// Shell list.
	ShellList& _shellList;
};

#endif // _BATTLECITY_KEYEVENTFILTER_H_
