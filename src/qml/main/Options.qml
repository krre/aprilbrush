import QtQuick 2.11
import QtQuick.Controls 1.6
import QtQuick.Layouts 1.2
import "../components"

WindowDialog {
    id: root
    title: qsTr("Options")
    width: 400
    height: 200

    onAccepted: {
    }

    ColumnLayout {
        width: parent.width
    }
}
