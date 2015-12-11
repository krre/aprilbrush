import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import "../../3rdparty/font-awesome/fontawesome.js" as FontAwesome

Item {
    id: root
    property bool isCurrentTab: mainRoot.currentTab === root
    property string title: qsTr("Unnamed")

    Rectangle {
        anchors.fill: parent

        Label {
            font.pointSize: 15
            font.family: "FontAwesome"
            text: FontAwesome.Icon.Plus
        }
    }
}
