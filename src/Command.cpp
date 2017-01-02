#include "include/Command.h"

#include <QDebug>

void MoveLeftCommand::Execute() noexcept
{
	qDebug() << QStringLiteral("MoveLeftCommand::Execute");
}

void MoveUpCommand::Execute() noexcept
{
	qDebug() << QStringLiteral("MoveUpCommand::Execute");
}

void MoveRightCommand::Execute() noexcept
{
	qDebug() << QStringLiteral("MoveRightCommand::Execute");
}

void MoveDownCommand::Execute() noexcept
{
	qDebug() << QStringLiteral("MoveDownCommand::Execute");
}

void ShotCommand::Execute() noexcept
{
	qDebug() << QStringLiteral("ShotCommand::Execute");
}

void NoCommand::Execute() noexcept
{
	//qDebug() << QStringLiteral("NoCommand::Execute");
}

void PauseCommand::Execute() noexcept
{
	qDebug() << QStringLiteral("PauseCommand::Execute");
}
