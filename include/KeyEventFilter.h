#ifndef _BATTLECITY_KEYEVENTFILTER_H_
#define _BATTLECITY_KEYEVENTFILTER_H_

#include "include/command/Command.h"

#include <QObject>

QT_FORWARD_DECLARE_CLASS(QEvent)

///
/// The KeyEventFilter class.
///

class KeyEventFilter : public QObject
{
	Q_OBJECT

public:
	KeyEventFilter(QObject *parent = Q_NULLPTR);

Q_SIGNALS:
	/// Emits command that has been entered.
	void Send(CommandShPtr cmd);

protected:
	/// Handles key press events.
	bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;
};

#endif // _BATTLECITY_KEYEVENTFILTER_H_
