import QtQuick 2.7

Item {
	x: userTank.coord.x; y: userTank.coord.y
	width: 30; height: 30
	focus: true
	smooth: true

	// Top view.
	Image {
		id: bodyId
		anchors.fill: parent
		source: userTank.body
		rotation: 180
	}

	Behavior on x { SmoothedAnimation { velocity: 110 } }
	Behavior on y { SmoothedAnimation { velocity: 110 } }

	Connections {
		target: userTank

		onCoordinatesChanged: {
			x = newCoord.x
			y = newCoord.y
		}

		onDirectionChanged: {
			bodyId.rotation = newDirect * 90 + 90
		}
	}
}
