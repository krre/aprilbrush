import QtQuick 2.0
import Qt.labs.folderlistmodel 1.0

Window {
    id: root
    title: "File Dialog"
    width: 400
    height: 300
    property string currentFilePath: currentFolderPath +
                                     (currentFolderPath.substr(-1) === "/" ? "" : "/") + fileNameText.text
    property string currentFolderPath: folderModel.folder.toString().replace("file:///", "")
    property string prevFolderPath
    property string currentFileName
    property bool openMode: true

    signal clicked

    Column {

        anchors.fill: parent
        width: parent.width
        spacing: 5

        Row {
            width: parent.width
            spacing: 5

            Button {
                id: upButton
                title: "Up"
                onClicked: {
                    var folderPath = folderModel.parentFolder
                    if (folderPath != "file:") {
                        folderModel.folder = folderPath
                        currentFolderPath = folderPath.toString().replace("file:///", "")
                    }
                }
            }

            Rectangle {
                width: parent.width - upButton.width - 5
                height: 20
                radius: 5
                clip: true

                TextEdit {
                    anchors.fill: parent
                    text: currentFolderPath
                    onTextChanged: if (text.substr(1) === ":/") folderModel.folder = "file:///" + text
                }
            }
        }

        ListView {
            id: fileView
            model: folderModel
            delegate: fileDelegate

            width: parent.width
            height: root.height - 90
            highlight: fileSelected
            clip: true
            highlightMoveDuration: 1
            spacing: 3
        }

        Component {
            id: fileDelegate
            Item {
                property alias filesText: filesText
                property var path: filePath
                width: root.width
                height: filesText.height
                Text {
                    id: filesText
                    text: fileName
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        fileView.currentIndex = index
                        if (folderModel.isFolder(index)) {                            
                            var parentPath = folderModel.parentFolder
                            folderModel.folder = "file:/" + filePath
                            currentFileName = ""
                            fileView.currentIndex = 0                            
                            var folderPath = folderModel.folder
                            currentFolderPath = folderPath.toString().substr(-2) === ".." ? parentPath : folderPath
                            currentFolderPath = currentFolderPath.replace("file:///", "")
                        }
                        else {
                            currentFileName = fileName
                        }
                    }
                }
            }
        }

        FolderListModel {
            id: folderModel
            folder: "file:/C:/"
            showDirs: true
            showDotAndDotDot: true
            showDirsFirst: true
            sortField: "Name"

        }

        Component {
            id: fileSelected
            Rectangle {
                width: root.width
                color: "lightgray"
                radius: 3
            }
        }

        Row {
            width: parent.width
            height: 20
            spacing: 5
            Rectangle {
                width: parent.width - openButton.width
                height: parent.height
                radius: 5
                clip: true

                TextEdit {
                    id: fileNameText
                    anchors.fill: parent
                    text: currentFileName
                    //onTextChanged: text = text.replace("\n", "")
                }
            }

            Button {
                id: openButton
                title: openMode ? "Open" : "Save"
                onClicked: root.clicked()
            }
        }
    }

    Component.onCompleted: {
        x = (parent.width - width) / 2
        y = (parent.height - height) / 2
    }
}
