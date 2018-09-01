import QtQuick 2.0

import "../js/ShellImpl.js" as ShellJsImpl

Item {
	width: 10; height: 10

	Image {
		anchors.fill: parent
		source: "../img/shell.png"
		smooth: true
	}

	Connections {
		target: shellArr

		onMove: {
			moveShell(index, x, y)
		}
	}
}
