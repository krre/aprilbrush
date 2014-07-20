import QtQuick 2.3
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1

ToolBar {
    RowLayout {
        ToolButton { action: actions.newImageAction }
        ToolButton { action: actions.openAction }
        ToolButton { action: actions.saveAction }
    }
}
