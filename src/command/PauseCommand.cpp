#include "include/command/PauseCommand.h"

#include <QDebug>

void PauseCommand::Execute() noexcept
{
	qDebug() << QStringLiteral("PauseCommand::Execute");
}
