import QtQuick 2.4
import QtQuick.Dialogs 1.1
import "utils.js" as Utils

FileDialog {
    id: fileDialog
    property int mode: 0 // 0 - open, 1 - save, 2 - export, 3 - folder
    visible: false
    title: mode == 0 ? qsTr("Open OpenRaster file") : mode == 1 ? qsTr("Save OpenRaster file") :
        mode == 2 ? qsTr("Export image to PNG") : qsTr("Select folder")
    selectExisting: mode == 0 ? true : false
    selectFolder: mode == 3 ? true : false
    nameFilters: mode == 2 ? "Images (*.png)" : "OpenRaster (*.ora)"

    onAccepted: {
        switch (mode) {
            case 0: Utils.openOra(fileDialog.fileUrl); break
            case 1: Utils.saveAsOra(fileDialog.fileUrl); break
            case 2: Utils.exportPng(fileDialog.fileUrl); break
        }
    }
}
