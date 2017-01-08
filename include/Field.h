#ifndef _BATTLECITY_FIELD_H_
#define _BATTLECITY_FIELD_H_

#include <QObject>
#include <QVector>

class Field : public QObject
{
	Q_OBJECT

public:
	/// Type alias.
	using FieldType = QVector<QVector<QChar>>;

public:
	/// Constructor.
	explicit Field(QObject *parent = Q_NULLPTR);

public:
	/// Loads stage.
	void loadStage(const int num);

private:
	/// Internal data structure.
	FieldType _field;
};

#endif // _BATTLECITY_FIELD_H_
