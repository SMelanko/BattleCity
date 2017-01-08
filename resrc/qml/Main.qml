import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import "./component"

ApplicationWindow {
	id: mainWndId
	visible: true
	width: 390; height: 360
	title: qsTr("Battle City")
	color: "#404040"

	Wood {
		x: 10; y: 10;
	}
	Wood {
		x: 20; y: 10;
	}
	Wood {
		x: 10; y: 20;
	}
	Wood {
		x: 20; y: 20;
	}

	Tank {
		id: userTankId
	}
}
