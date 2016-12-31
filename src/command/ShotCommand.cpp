#include "include/command/ShotCommand.h"

#include <QDebug>

void ShotCommand::Execute() noexcept
{
	qDebug() << QStringLiteral("ShotCommand::Execute");
}
