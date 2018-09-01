var _shellArr = []

/// Creates shell.
function createShell(x, y) {
	var _qmlComponent = Qt.createComponent("../qml/Shell.qml");

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

		dynObj.x = x;
		dynObj.y = y;

		_shellArr.push(dynObj)
	} else {
		console.log("Error loading qml component");
		console.log(_qmlComponent.errorString());

		return null;
	}
}

/// Moves a shell.
function moveShell(index, x, y) {
	_shellArr[index].x = x;
	_shellArr[index].y = y;
}

/// Removes a shell.
function removeShell(index) {
	_shellArr.splice(index, 1);
}
