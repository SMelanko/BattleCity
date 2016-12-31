#include "include/command/MoveLeftCommand.h"

#include <QDebug>

void MoveLeftCommand::Execute() noexcept
{
	qDebug() << QStringLiteral("MoveLeftCommand::Execute");
}
