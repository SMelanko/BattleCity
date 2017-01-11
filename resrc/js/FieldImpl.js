var _maxFieldRows = 13;
var _maxFieldColumns = 13;
var _maxFieldIndex = _maxFieldColumns * _maxFieldRows;
var _field = new Array(_maxFieldIndex);
var _componentSize = 10;
var _qmlComponent = null;

/// Index function used instead of a 2D array.
function index(row, column) {
	return (row * column) + column;
}

/// Creates qml component.
function createBlock(row, column) {
	if (_qmlComponent == null) {
		_qmlComponent = Qt.createComponent("../qml/component/Wood.qml");
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
		dynObj.width = _componentSize;
		dynObj.height = _componentSize;

		_field[index(row, column)] = dynObj;
	} else {
		console.log("error loading block component");
		console.log(_qmlComponent.errorString());
		return false;
	}

	return true;
}

/// Creates the entire battlefield.
function createField() {
	// Delete blocks from previous stage.
	for (var i = 0; i < _maxFieldIndex; ++i) {
		if (_field[i] != null) {
			_field[i].destroy();
		}
	}

	// Calculate board size.
	_maxFieldRows = 13; // TODO:
	_maxFieldColumns = 13; // TODO:
	_maxFieldIndex = _maxFieldRows * _maxFieldColumns;

	// Initialize field.
	_field = new Array(_maxFieldIndex);

	for (var row = 0; row < _maxFieldRows; ++row) {
		for (var column = 0; column < _maxFieldColumns; ++column) {
			_field[index(row, column)] = null;
			createBlock(row, column);
		}
	}
}
