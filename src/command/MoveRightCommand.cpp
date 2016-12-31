#include "include/command/MoveRightCommand.h"

#include <QDebug>

void MoveRightCommand::Execute() noexcept
{
	qDebug() << QStringLiteral("MoveRightCommand::Execute");
}
