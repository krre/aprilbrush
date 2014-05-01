import QtQuick 2.2
import QtQuick.Controls 1.1

Item {
    property alias newAction: newAction
    property alias openAction: openAction
    property alias saveAction: saveAction
    property alias saveAsAction: saveAsAction
    property alias closeAction: closeAction
    property alias closeAllAction: closeAllAction
    property alias closeOthersAction: closeOthersAction
    property alias quitAction: quitAction

    Action {
        id: newAction
        text: qsTr("New")
        shortcut: StandardKey.New
        onTriggered: {
            tabView.addTab("Untitled " + (tabView.count + 1), canvasArea)
            tabView.currentIndex = tabView.count - 1
        }
        tooltip: "New an Image"
    }

    Action {
        id: openAction
        text: qsTr("Open")
        shortcut: StandardKey.Open
        onTriggered: fileDialog.open()
        tooltip: "Open an Image"
    }

    Action {
        id: saveAction
        text: qsTr("Save")
        shortcut: StandardKey.Save
        onTriggered: print("save")
        tooltip: "Save an Image"
    }

    Action {
        id: saveAsAction
        text: qsTr("Save As...")
        shortcut: StandardKey.SaveAs
        onTriggered: print("save as")
        tooltip: "Save as an Image"
    }

    Action {
        id: closeAction
        text: qsTr("Close")
        shortcut: StandardKey.Close
        onTriggered: tabView.removeTab(tabView.currentIndex)
        tooltip: "Close as an Image"
        enabled: tabView.count > 0
    }

    Action {
        id: closeAllAction
        text: qsTr("Close All")
        onTriggered: {
            while (tabView.count) {
                tabView.removeTab(0)
            }
        }
        tooltip: "Close all Images"
        enabled: tabView.count > 0
    }

    Action {
        id: closeOthersAction
        text: qsTr("Close Others")
        onTriggered: {
            var currentTab = tabView.getTab(tabView.currentIndex)
            var i = 0
            while (tabView.count > 1) {
                var tab = tabView.getTab(i)
                if (tab !== currentTab) {
                    tabView.removeTab(i)
                } else {
                    i++
                }
            }
        }
        tooltip: "Close others Images"
        enabled: tabView.count > 1
    }

    Action {
        id: quitAction
        text: qsTr("Quit")
        shortcut: StandardKey.Quit
        onTriggered: Qt.quit()
        tooltip: "Quit"
    }
}

