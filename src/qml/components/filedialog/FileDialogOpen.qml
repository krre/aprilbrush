import QtQuick 2.10
import "../../../js/utils.js" as Utils

FileDialogBase {
     title: qsTr("Open OpenRaster file")
     nameFilters: [ qsTr("OpenRaster (*.ora)"), qsTr("All files (*)") ]
     onAccepted: Utils.openOra(Core.urlToPath(fileUrl))
}
