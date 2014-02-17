import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1

Item {
    id: root
    property alias model: listView.model
    property alias currentIndex: listView.currentIndex
    property alias count: listView.count
    property alias listView: listView

    signal clicked

    ScrollView {
        anchors.fill: parent

        ListView {
            id: listView
            delegate: listDelegate
            highlight: listSelected
            highlightMoveDuration: 1
            orientation: ListView.Vertical
            spacing: 4
        }
    }

    Component {
        id: listDelegate

        Text {
            text: name
            width: listView.width
            height: 20
            color:  "white"
            MouseArea {
                anchors.fill: parent
                onClicked: { listView.currentIndex = index; root.clicked() }
            }
        }
    }

    Component {
        id: listSelected
        Rectangle {
            width: listView.width
            height: 20
            color: "#4444e8"
        }
    }
}
