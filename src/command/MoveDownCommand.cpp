#include "include/command/MoveDownCommand.h"

#include <QDebug>

void MoveDownCommand::Execute() noexcept
{
	qDebug() << QStringLiteral("MoveDownCommand::Execute");
}
