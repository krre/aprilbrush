import QtQuick 2.0

Item {
    id: root

    property color initColor: "white"

    width: 100
    height: 100
    Rectangle {
        anchors.fill: parent
        color: initColor
    }

    ListModel {
        id: layersModel
        ListElement {name: "Background"}
        ListElement {name: "Layer00"}
    }


}


