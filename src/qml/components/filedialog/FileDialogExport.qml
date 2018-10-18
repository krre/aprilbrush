import QtQuick 2.11
import "../../../js/utils.js" as Utils

FileDialogBase {
     title: qsTr("Export image to PNG")
     nameFilters: [ qsTr("Images (*.png)"), qsTr("All files (*)") ]
     selectExisting: false
     onAccepted: Utils.exportPng(Core.urlToPath(fileUrl))
}
