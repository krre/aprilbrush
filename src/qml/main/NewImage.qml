import QtQuick 2.6
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtQuick.Window 2.2
import "../components"
import "../../js/utils.js" as Utils

WindowDialog {
    id: root
    title: qsTr("New Image")
    width: 400
    height: 200

    onAccepted: {
        Settings.setValue("NewImage", "width", widthSize.value)
        Settings.setValue("NewImage", "height", heightSize.value)
        Utils.newTab(name.text, false)
    }

    GridLayout {
        width: parent.width
        columns: 2

        Label {
            text: qsTr("Name:")
        }

        TextField {
            id: name
            Layout.fillWidth: true
            text: qsTr("Unnamed")
            Component.onCompleted: forceActiveFocus()
        }

        Label {
            text: qsTr("Width:")
        }

        SpinBox {
            id: widthSize
            implicitWidth: 80
            maximumValue: 2000
            minimumValue: 1
            value: Settings.value("NewImage", "width", Screen.width)
        }

        Label {
            text: qsTr("Height:")
        }

        SpinBox {
            id: heightSize
            implicitWidth: 80
            maximumValue: 2000
            minimumValue: 1
            value: Settings.value("NewImage", "height", Screen.height)
        }

        ButtonBase {
            Layout.columnSpan: 2
            text: qsTr("Screen Size")
            onClicked: {
                widthSize.value = Screen.width
                heightSize.value = Screen.height
            }
        }
    }
}
