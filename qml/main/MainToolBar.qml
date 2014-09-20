import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

ToolBar {
    RowLayout {
        ToolButton { action: actions.newAction }
        ToolButton { action: actions.openAction }
        ToolButton { action: actions.saveAction }
        ToolButton { action: actions.clearAction }
    }
}
