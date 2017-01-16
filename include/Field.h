#ifndef _BATTLECITY_FIELD_H_
#define _BATTLECITY_FIELD_H_

#include <QObject>
#include <QVector>

#include <memory>

/*
	Field components type:
		'0' - brick wall;
		'1' - concrete wall;
		'2' - ground;
		'3' - ice;
		'4' - water;
		'5' - wood;
		'b' - user base;
*/

class Field : public QObject
{
	Q_OBJECT

public:
	/// Type alias.
	using Size = int;
	using Component = QChar;
	using Data = QVector<QString>;

public:
	/// Constructor.
	explicit Field(QObject *parent = Q_NULLPTR);

public:
	/// Returns count of the columns.
	Q_INVOKABLE Size columns() const Q_DECL_NOEXCEPT;
	/// Returns component's type.
	Q_INVOKABLE Component item(const Size row,
		const Size column) const Q_DECL_NOEXCEPT;
	Component item1(const int x, const int y) const Q_DECL_NOEXCEPT;
	/// Loads stage.
	void loadStage(const int num);
	/// Returns count of the rows.
	Q_INVOKABLE Size rows() const Q_DECL_NOEXCEPT;

private:
	/// Internal data structure.
	Data _field;
};

/// Field alias.
using FieldShPtr = std::shared_ptr<Field>;

///
/// Inline implementation of the Field class methods.
///

inline Field::Size Field::columns() const Q_DECL_NOEXCEPT
{
	return _field[0].size();
}

inline Field::Component Field::item(const Size row,
	const Size column) const Q_DECL_NOEXCEPT
{
	return _field[row][column];
}

inline Field::Component Field::item1(const int x,
	const int y) const Q_DECL_NOEXCEPT
{
	return _field[y / 10][x / 10];
}

inline Field::Size Field::rows() const Q_DECL_NOEXCEPT
{
	return _field.size();
}

#endif // _BATTLECITY_FIELD_H_
