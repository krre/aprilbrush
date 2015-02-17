import QtQuick 2.4
import QtQuick.Dialogs 1.1
import "utils.js" as Utils
import "enums.js" as Enums

FileDialog {
    property int mode: Enums.FileOpen // 0 - open, 1 - save, 2 - export, 3 - folder
    visible: false
    title: mode == Enums.FileOpen ? qsTr("Open OpenRaster file") : mode == Enums.FileSave ? qsTr("Save OpenRaster file") :
        mode == Enums.FileExport ? qsTr("Export image to PNG") : qsTr("Select folder")
    selectExisting: mode == Enums.FileOpen
    selectFolder: mode == Enums.FileFolder
    nameFilters: mode == Enums.FileExport ? "Images (*.png)" : "OpenRaster (*.ora)"

    onAccepted: {
        switch (mode) {
            case Enums.FileOpen: Utils.openOra(fileUrl); break
            case Enums.FileSave: Utils.saveAsOra(fileUrl); break
            case Enums.FileExport: Utils.exportPng(fileUrl); break
        }
    }
}
