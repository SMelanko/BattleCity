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
	explicit KeyEventFilter(QObject *parent = Q_NULLPTR) Q_DECL_NOEXCEPT;

Q_SIGNALS:
	/// Emits command that has been entered.
	void Send(CommandShPtr cmd);

protected:
	/// Handles key press events.
	bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;

private:
	/// Gets key code from the event object.
	KeyCode GetKey(QEvent* event) const;
	/// Creates command according to pressed key.
	CommandShPtr MakeCommand(const KeyCode key) const;

private:
	/// Set of pressed keys.
	std::set<KeyCode> _keys;
};

#endif // _BATTLECITY_KEYEVENTFILTER_H_
