#include "include/KeyEventFilter.h"

#include <QDebug>
#include <QEvent>
#include <QKeyEvent>

#include "include/Command.h"

KeyEventFilter::KeyEventFilter(TankShPtr userTank, ShellList& shellList,
	QObject *parent) Q_DECL_NOEXCEPT
	: QObject{ parent }
	, _userTank{ userTank }
	, _shellList{ shellList }
{
}

bool KeyEventFilter::eventFilter(QObject *, QEvent *event)
{
	bool result = false;

	if (event->type() == QEvent::KeyPress) {
		QKeyEvent *ke = static_cast<QKeyEvent *>(event);
		const auto key = ke->key();

		switch (key) {
		case Qt::Key_Left:
		case Qt::Key_Up:
		case Qt::Key_Right:
		case Qt::Key_Down:
			setMoveCommand(makeCommand(key));
			result = true;
			break;
		case Qt::Key_Space:
			setShotCommand(makeCommand(key));
			result = true;
			break;
		}
	} else if (event->type() == QEvent::KeyRelease) {
		QKeyEvent *ke = static_cast<QKeyEvent *>(event);
		const auto key = ke->key();

		switch (key) {
		case Qt::Key_Left:
		case Qt::Key_Up:
		case Qt::Key_Right:
		case Qt::Key_Down:
			removeMoveCommand();
			result = true;
			break;
		case Qt::Key_Space:
			removeShotCommand();
			result = true;
			break;
		}
	}

	return result;
}

CommandShPtr KeyEventFilter::makeCommand(const KeyCode key) const
{
	if (key == Qt::Key_Left) {
		return std::make_shared<MoveLeftCommand>(_userTank);
	} else if (key == Qt::Key_Up) {
		return std::make_shared<MoveUpCommand>(_userTank);
	} else if (key == Qt::Key_Right) {
		return std::make_shared<MoveRightCommand>(_userTank);
	} else if (key == Qt::Key_Down) {
		return std::make_shared<MoveDownCommand>(_userTank);
	} else if (key == Qt::Key_Space) {
		return std::make_shared<ShotCommand>(_userTank, _shellList);
	} else {
		return std::make_shared<NoCommand>();
	}
}
