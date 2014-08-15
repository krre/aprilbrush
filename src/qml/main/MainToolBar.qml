import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

ToolBar {
    RowLayout {
        ToolButton { action: actions.newImageAction }
        ToolButton { action: actions.openAction }
        ToolButton { action: actions.saveAction }
        ToolButton { action: actions.clearAction }
        ToolButton {
            text: "Ora"
            onClicked: {
                var data = currentTab.canvas.toDataURL()
                data = data.substring(22, data.length) // cutting first block "data:image/png;base64,"
                var layerList = []
                layerList.push(data)
                var oraPath = "/home/krre/work/aprilbrush/test.ora"

                coreLib.writeOra(oraPath, imageSize, layerList)
            }
        }
    }
}
