import QtQuick 2.5
import "../../../js/utils.js" as Utils

FileDialogBase {
     title: qsTr("Open OpenRaster file")
     nameFilters: [ qsTr("OpenRaster (*.ora)"), qsTr("All files (*)") ]
     onAccepted: Utils.openOra(coreLib.urlToPath(fileUrl))
}
