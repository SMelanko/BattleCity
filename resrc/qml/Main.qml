import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import "./component"

ApplicationWindow {
	visible: true
	width: 240; height: 320
	//width: 780; height: 720
	title: qsTr("Battle City")

	Text {
		x: 10; y: 10
		width: 100; height: 100
		visible: true
		text: _msg.author // invokes Message::author() to get this value

		Component.onCompleted: {
			_msg.author = "Jonah" // invokes Message::setAuthor()
			_msg.postMessage("Hello from QML", 123);
		}
	}

/*
	BrickWall {
		x: 0; y: 0
	}

	ConcreteWall {
		x: 20; y: 0
	}

	Ground {
		x: 40; y: 0
	}

	Ice {
		x: 60; y: 0
	}

	Water {
		x: 80; y: 0
	}

	Wood {
		x: 100; y: 0
	}
*/
}
