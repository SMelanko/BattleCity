import QtQuick 2.0

import "../js/FieldImpl.js" as FieldJsImpl

Item {
	Component.onCompleted: {
		FieldJsImpl.createField();
	}
}
