import QtQuick 2.6
import QtQuick.Controls 1.5

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
