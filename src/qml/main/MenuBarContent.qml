import QtQuick 2.2
import QtQuick.Controls 1.1

MenuBar {
    Menu {
        title: qsTr("File")

        MenuItem { action: actions.newAction }
        MenuItem { action: actions.openAction }
        MenuItem { action: actions.saveAction }
        MenuItem { action: actions.saveAsAction }
        MenuSeparator {}
        MenuItem { action: actions.closeAction }
        MenuItem { action: actions.closeAllAction }
        MenuItem { action: actions.closeOthersAction }
        MenuSeparator {}
        MenuItem { action: actions.quitAction }
    }

    Menu {
        title: qsTr("Edit")
    }

    Menu {
        title: qsTr("View")

        MenuItem {
            text: qsTr("Tool Bar")
            checkable: true
            checked: true
            onTriggered: toolBar.visible = !toolBar.visible
        }

        MenuItem {
            text: qsTr("Status Bar")
            checkable: true
            checked: true
            onTriggered: statusBar.visible = !statusBar.visible
        }

        MenuItem {
            text: colorPicker.title
            checkable: true
            checked: colorPicker.visible
            onTriggered: colorPicker.visible = !colorPicker.visible
        }
    }

    Menu {
        title: qsTr("Help")

        MenuItem {
            text: qsTr("About...")
            onTriggered: print("about")
        }
    }
}
