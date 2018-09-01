#include "include/Field.h"
#include "include/Shell.h"

FlyableObject::FlyableObject(const Coordinates& coord, const Direction direct,
	const Speed speed, QObject *parent) Q_DECL_NOEXCEPT
	: QObject{ parent }
	, _coord{ coord }
	, _direct{ direct }
	, _speed{ speed }
{
	qRegisterMetaType<Coordinates>("Coordinates");
	qRegisterMetaType<Direction>("Direction");
	qRegisterMetaType<Speed>("Speed");
}

Shell::Shell(FieldShPtr field, const Coordinates& coord, const Direction direct,
	const Speed speed, QObject *parent) Q_DECL_NOEXCEPT
	: FlyableObject(coord, direct, speed, parent)
	, _field{ field }
	, _state{ CREATE }
{
	_field->setItem(coord.x(), coord.y(), QLatin1Char{ 's' });
}
