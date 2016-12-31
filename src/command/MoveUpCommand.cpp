#include "include/command/MoveUpCommand.h"

#include <QDebug>

void MoveUpCommand::Execute() noexcept
{
	qDebug() << QStringLiteral("MoveUpCommand::Execute");
}
