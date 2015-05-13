import QtQuick 2.4
import QtQuick.Dialogs 1.1
import "utils.js" as Utils
import "enums.js" as Enums

FileDialog {
    property int mode: Enums.FileOpen
    title: mode == Enums.FileOpen ? qsTr("Open OpenRaster file") : mode == Enums.FileSave ? qsTr("Save OpenRaster file") :
        mode == Enums.FileExport ? qsTr("Export image to PNG") : qsTr("Select folder")
    selectExisting: mode == Enums.FileOpen
    selectFolder: mode == Enums.FileFolder
    nameFilters: mode == Enums.FileExport ? qsTr("Images (*.png)") : qsTr("OpenRaster (*.ora)")

    Component.onCompleted: open()

    onAccepted: {
        switch (mode) {
            case Enums.FileOpen: Utils.openOra(coreLib.urlToPath(fileUrl)); break
            case Enums.FileSave: Utils.saveAsOra(coreLib.urlToPath(fileUrl)); break
            case Enums.FileExport: Utils.exportPng(coreLib.urlToPath(fileUrl)); break
        }
    }
}
