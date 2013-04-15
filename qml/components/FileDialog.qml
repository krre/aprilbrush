import QtQuick 2.0
import Qt.labs.folderlistmodel 1.0

Window {
    id: root
    title: "File Dialog"
    width: 400
    height: 300

    property int mode: 0
    property string currentFolderPath: folderModel.folder
    property string currentFileName: fileNameText.text
    property string currentFilePath: currentFolderPath +
                                     (currentFolderPath.substring[-1] === "/" ? "" : "/") + currentFileName
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
                    var re = new RegExp("file:\/\/\/.:\/$", "i")
                    if ((currentFolderPath != "file:///") && !re.test(currentFolderPath))
                        folderModel.folder = folderModel.parentFolder
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
                    onTextChanged: folderModel.folder = text
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
                        if (fileIsDir) {
                            if (fileName == "..")
                                folderModel.folder = folderModel.parentFolder
                            else
                                folderModel.folder += (folderModel.folder.toString().substr(-1) === "/" ? "" : "/")  + fileName
                            fileView.currentIndex = 0
                        }
                        else {
                            fileNameText.text = fileName
                        }
                    }
                }
            }
        }

        FolderListModel {
            id: folderModel
            folder: coreLib.rootFolder()
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
                }
            }

            Button {
                id: openButton
                title: mode === 0 ? "Open" : (mode === 1 ? "Save" : "Export")
                onClicked: root.clicked()
            }
        }
    }

    Component.onCompleted: {
        x = (parent.width - width) / 2
        y = (parent.height - height) / 2
    }
}
