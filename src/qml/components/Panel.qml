import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1

Rectangle {
    default property alias content: content.data
    property string title
    color: sysPalette.window

    Item {
        id: content
        anchors.fill: parent
        anchors.margins: 7
    }
}
