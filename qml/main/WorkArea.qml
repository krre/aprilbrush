import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1

Item {
    id: root
    property bool isCurrentTab: mainRoot.currentTab === root
    property string title: qsTr("Unnamed")

    Rectangle {
        anchors.fill: parent
    }
}
