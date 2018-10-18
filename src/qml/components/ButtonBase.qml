import QtQuick 2.11
import QtQuick.Controls 1.6

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
