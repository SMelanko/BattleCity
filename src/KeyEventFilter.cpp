#include "include/KeyEventFilter.h"

#include <QDebug>
#include <QEvent>
#include <QKeyEvent>

#include "include/Command.h"

KeyEventFilter::KeyEventFilter(QObject *parent) Q_DECL_NOEXCEPT
	: QObject{ parent }
{
}

bool KeyEventFilter::eventFilter(QObject *, QEvent *event)
{
	bool result = false;

	if (event->type() == QEvent::KeyPress) {
		QKeyEvent *ke = static_cast<QKeyEvent *>(event);
		const auto key = ke->key();

		//qDebug() << QStringLiteral("QEvent::KeyPress");

		switch (key) {
		case Qt::Key_Left:
		case Qt::Key_Up:
		case Qt::Key_Right:
		case Qt::Key_Down:
		case Qt::Key_Space:
			if (!ke->isAutoRepeat()) {
				_keys.insert(key);
			}
			result = true;
			break;
		}
	} else if (event->type() == QEvent::KeyRelease) {
		QKeyEvent *ke = static_cast<QKeyEvent *>(event);
		const auto key = ke->key();

		//qDebug() << QStringLiteral("QEvent::KeyRelease");

		switch (key) {
		case Qt::Key_Left:
		case Qt::Key_Up:
		case Qt::Key_Right:
		case Qt::Key_Down:
		case Qt::Key_Space:
			_keys.erase(key);
			result = true;
			break;
		}
	}

	if (result) {
		for (const auto& key : _keys) {
			Q_EMIT Send(MakeCommand(key));
		}
	}

	return result;
}

KeyEventFilter::KeyCode KeyEventFilter::GetKey(QEvent* event) const
{
	return static_cast<QKeyEvent *>(event)->key();
}

CommandShPtr KeyEventFilter::MakeCommand(const KeyCode key) const
{
	if (key == Qt::Key_Left) {
		return std::make_shared<MoveLeftCommand>();
	} else if (key == Qt::Key_Up) {
		return std::make_shared<MoveUpCommand>();
	} else if (key == Qt::Key_Right) {
		return std::make_shared<MoveRightCommand>();
	} else if (key == Qt::Key_Down) {
		return std::make_shared<MoveDownCommand>();
	} else if (key == Qt::Key_Space) {
		return std::make_shared<ShotCommand>();
	} else {
		return std::make_shared<NoCommand>();
	}
}
