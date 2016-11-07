import QtQuick 2.8
import QtQml 2.2
import QtQuick.Controls 1.5
import "../../js/utils.js" as Utils
import "../../js/enums.js" as Enums
import "../../js/undo.js" as Undo

MenuBar {
    property alias recentFilesModel: recentFilesModel
    property alias docker: docker

    Menu {
        title: qsTr("File")

        MenuItem {
            text: qsTr("New...")
            shortcut: "Ctrl+N"
            onTriggered: Utils.createDynamicObject(mainRoot, "qrc:/qml/main/NewImage.qml")
        }

        MenuItem {
            text: qsTr("Open...")
            shortcut: "Ctrl+O"
            onTriggered: Utils.createDynamicObject(mainRoot, "qrc:/qml/components/filedialog/FileDialogOpen.qml")
        }

        Menu {
            id: recentFilesMenu
            title: qsTr("Recent Files")
            enabled: recentFilesModel.count > 0

            Instantiator {
                model: recentFilesModel

                MenuItem {
                    text: model.filePath
                    onTriggered: Utils.openOra(text)
                }

                onObjectAdded: recentFilesMenu.insertItem(index, object)
                onObjectRemoved: recentFilesMenu.removeItem(object)
            }

            MenuSeparator {
                visible: recentFilesModel.count > 0
            }

            MenuItem {
                text: qsTr("Clear Menu")
                onTriggered: recentFilesModel.clear()
            }

            ListModel {
                id: recentFilesModel
            }
        }

        MenuSeparator {}

        MenuItem {
            text: qsTr("Save")
            shortcut: "Ctrl+S"
            onTriggered: {
                if (!currentTab.oraPath) {
                    Utils.createDynamicObject(mainRoot, "qrc:/qml/components/filedialog/FileDialogSave.qml")
                } else {
                    Utils.saveOra()
                }
            }
            enabled: currentTab && currentTab.isDirty
        }

        MenuItem {
            text: qsTr("Save As...")
            shortcut: "Ctrl+Shift+S"
            onTriggered: Utils.createDynamicObject(mainRoot, "qrc:/qml/components/filedialog/FileDialogSave.qml")
            enabled: currentTab
        }

        MenuItem {
            text: qsTr("Export...")
            shortcut: "Ctrl+E"
            onTriggered: Utils.createDynamicObject(mainRoot, "qrc:/qml/components/filedialog/FileDialogExport.qml")
            enabled: currentTab && layerModel.count > 0
        }

        MenuSeparator {}

        MenuItem {
            text: qsTr("Close")
            shortcut: "Ctrl+W"
            onTriggered: tabView.removeTab(tabView.currentIndex)
            enabled: tabView.count > 0
        }

        MenuItem {
            text: qsTr("Close All")
            shortcut: "Ctrl+Shift+W"
            onTriggered: {
                while (tabView.count > 0) {
                    tabView.removeTab(0)
                }
            }
            enabled: tabView.count > 0
        }

        MenuItem {
            text: qsTr("Close Other")
            enabled: tabView.count > 1
            onTriggered: {
                var i = 0
                while (tabView.count > 1) {
                    if (i !== tabView.currentIndex) {
                        tabView.removeTab(i)
                    } else {
                        i++
                    }
                }
            }
        }

        MenuSeparator {}

        MenuItem {
            text: qsTr("Exit")
            shortcut: "Ctrl+Q"
            onTriggered: mainRoot.close()
        }
    }

    Menu {
        title: qsTr("Edit")

        MenuItem {
            text: qsTr("Undo")
            shortcut: "Ctrl+Z"
            onTriggered: {
                undoManager.undoView.decrementCurrentIndex()
                undoManager.run(undoManager.currentIndex)
            }
            enabled: undoManager.currentIndex > 0
        }

        MenuItem {
            text: qsTr("Redo")
            shortcut: "Ctrl+Shift+Z"
            onTriggered: {
                undoManager.undoView.incrementCurrentIndex()
                undoManager.run(undoManager.currentIndex)
            }
            enabled: undoModel ? undoManager.currentIndex < undoModel.count - 1 : false
        }

        MenuItem {
            text: qsTr("Clear")
            shortcut: "Delete"
            onTriggered: undoManager.add(Undo.clearLayer())
            enabled: layerManager.currentIndex >= 0
        }
    }

    Menu {
        title: qsTr("Layer")

        MenuItem { action: actions.newLayerAction }

        MenuItem { action: actions.deleteLayerAction }

        MenuItem { action: actions.mergeLayerAction }

        MenuItem { action: actions.duplicateLayerAction }

        MenuItem { action: actions.upLayerAction }

        MenuItem { action: actions.downLayerAction }
    }

    Menu {
        title: qsTr("View")

        MenuItem {
            id: docker
            text: qsTr("Docker")
            checkable: true
            shortcut: "Tab"
            checked: Settings.value("Main", "docker", true) === "true"
        }

        MenuItem {
            text: qsTr("Zoom In")
            shortcut: "."
            onTriggered: currentTab.zoomIn()
        }

        MenuItem {
            text: qsTr("Zoom Out")
            shortcut: ","
            onTriggered: currentTab.zoomOut()
        }

        MenuItem {
            text: qsTr("Rotation")
            shortcut: "R"
            onTriggered: currentTab.rotation += 90
        }

        MenuItem {
            text: qsTr("Mirror")
            shortcut: "M"
            onTriggered: currentTab.mirror *= -1
        }

        MenuItem {
            text: qsTr("Reset")
            shortcut: "F12"
            onTriggered: currentTab.resetTransform()
        }

        MenuItem {
            text: qsTr("Full Screen")
            shortcut: "F11"
            checkable: true
            onTriggered: checked ? mainRoot.showFullScreen() : mainRoot.showNormal()
        }
    }

    Menu {
        title: qsTr("Tools")

        MenuItem {
            text: qsTr("Options...")
            onTriggered: Utils.createDynamicObject(mainRoot, "qrc:/qml/main/Options.qml")
        }
    }

    Menu {
        title: qsTr("Help")

        MenuItem {
            text: qsTr("About %1...".arg(Qt.application.name))
            onTriggered: Utils.createDynamicObject(mainRoot, "qrc:/qml/main/About.qml")
        }
    }
}
