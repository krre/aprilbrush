import QtQuick 2.6
import QtQuick.Controls 1.4

Button {
    objectName: "ButtonBase"
    activeFocusOnPress: true
    isDefault: activeFocus

    Action {
        shortcut: "Return"
        enabled: isDefault
        onTriggered: clicked()
    }
}
