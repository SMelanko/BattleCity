import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import "./component"

ApplicationWindow {
	id: _mainWndId
	visible: true
	width: 390; height: 390
	title: qsTr("Battle City")
	color: "#404040"

	Field {
		id: _fieldId
		anchors.fill: parent
	}

	Tank {
		id: _userTankId
	}
}
