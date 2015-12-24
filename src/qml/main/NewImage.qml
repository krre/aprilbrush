import QtQuick 2.6
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import "../components"

WindowDialog {
    id: root
    title: qsTr("New Image")
    width: 400
    height: 200

    onAccepted: {
    }

    ColumnLayout {
        width: parent.width
    }
}
