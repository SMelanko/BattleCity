var _maxFieldRows = 1;
var _maxFieldColumns = 1;
var _maxFieldIndex = _maxFieldColumns * _maxFieldRows;
var _field = new Array(_maxFieldIndex);
var _componentSize = 10;

/// Deletes all field components.
function clearField() {
	for (var i = 0; i < _maxFieldIndex; ++i) {
		if (_field[i] != null) {
			_field[i].destroy();
		}
	}
}

/// Creates qml component.
function createComponent(item, row, column) {
	var _qmlComponent = createComponentFactory(item);

	if (_qmlComponent == null) {
		return null;
	}

	if (_qmlComponent.status == Component.Ready) {
		var dynObj = _qmlComponent.createObject(_fieldId);

		if (dynObj == null) {
			console.log("Error creating qml component");
			console.log(_qmlComponent.errorString());
			return false;
		}

		dynObj.x = column * _componentSize;
		dynObj.y = row * _componentSize;

		return dynObj;
	} else {
		console.log("Error loading block component");
		console.log(_qmlComponent.errorString());
		return null;
	}
}

/// Creates field component.
function createComponentFactory(item) {
	if (item === '0') {
		return Qt.createComponent("../qml/component/BrickWall.qml");
	} else if (item === '1') {
		return Qt.createComponent("../qml/component/ConcreteWall.qml");
	} else if (item === '3') {
		return Qt.createComponent("../qml/component/Ice.qml");
	} else if (item === '4') {
		return Qt.createComponent("../qml/component/Water.qml");
	} else if (item === '5') {
		return Qt.createComponent("../qml/component/Wood.qml");
	} else if (item === 'b') {
		return Qt.createComponent("../qml/component/Base.qml");
	} else {
		return null;
	}
}

/// Creates the entire battlefield.
function createField() {
	clearField();

	_maxFieldRows = field.rows();
	_maxFieldColumns = field.columns();
	_maxFieldIndex = _maxFieldRows * _maxFieldColumns;

	// Initialize field.
	_field = new Array(_maxFieldIndex);

	for (var row = 0; row < _maxFieldRows; ++row) {
		for (var column = 0; column < _maxFieldColumns; ++column) {
			var item = field.item(row, column);
			_field[index(row, column)] = createComponent(item, row, column);
		}
	}
}

/// Index function used instead of a 2D array.
function index(row, column) {
	return (row * column) + column;
}
