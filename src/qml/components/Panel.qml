import QtQuick 2.6
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3

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
