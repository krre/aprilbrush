import QtQuick 2.3
import QtQuick.Dialogs 1.1
import "utils.js" as Utils

FileDialog {
    id: fileDialog
    property int mode: 0 // 0 - open, 1 - save, 2 - export, 3 - folder
    visible: true

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
    onVisibleChanged: if (!visible) { destroy() }
}
