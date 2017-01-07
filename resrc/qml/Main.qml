import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import "./component"

ApplicationWindow {
	visible: true
	width: 480; height: 320
	title: qsTr("Battle City")
	color: "#404040"

	Tank {
		id: userTankId
	}
}
