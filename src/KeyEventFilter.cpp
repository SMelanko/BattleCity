#include "include/KeyEventFilter.h"

#include <QDebug>
#include <QEvent>
#include <QKeyEvent>

#include "include/command/MoveDownCommand.h"
#include "include/command/MoveLeftCommand.h"
#include "include/command/MoveRightCommand.h"
#include "include/command/MoveUpCommand.h"
#include "include/command/PauseCommand.h"
#include "include/command/ShotCommand.h"

KeyEventFilter::KeyEventFilter(QObject *parent)
	: QObject{ parent }
{
}

bool KeyEventFilter::eventFilter(QObject *watched, QEvent *event)
{
	Q_UNUSED(watched)

	bool result = false;
	CommandShPtr cmd = Q_NULLPTR;

	if (event->type() == QEvent::KeyPress) {
		QKeyEvent *ke = static_cast<QKeyEvent *>(event);
		const auto key = ke->key();

		if (key == Qt::Key_Left) {
			cmd = std::make_shared<MoveLeftCommand>();
			result = true;
		} else if (key == Qt::Key_Up) {
			cmd = std::make_shared<MoveUpCommand>();
			result = true;
		} else if (key == Qt::Key_Right) {
			cmd = std::make_shared<MoveRightCommand>();
			result = true;
		} else if (key == Qt::Key_Down) {
			cmd = std::make_shared<MoveDownCommand>();
			result = true;
		} else if (key == Qt::Key_Space) {
			cmd = std::make_shared<ShotCommand>();
			result = true;
		} else if (key == Qt::Key_Return) {
			cmd = std::make_shared<PauseCommand>();
			result = true;
		}
	}

	if (result && cmd) {
		Send(cmd);
	}

	return result;
}
