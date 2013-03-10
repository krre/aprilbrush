import QtQuick 2.0
import QtQuick.Window 2.0
import Drawing 1.0

Item {
    id: root

    property color initColor: "white"
    property variant layersModel: layers

    width: 500
    height: 500


    // White layer
    PaintSpace {
        id: space
        width: Screen.width
        height: Screen.height
        color: "white"
    }


    // Transparent layer
    PaintSpace {
        width: Screen.width
        height: Screen.height
        //color: "red"
    }

    PathView {
        model: layersModel
        delegate: imgDelegate

        anchors.centerIn: parent
        path: Path {
            PathAttribute { name: "z"; value: 9999.0 }
            PathLine { x: 0; y: 0 }
            PathAttribute { name: "z"; value: 0.0 }
        }
    }

    ListModel {
        id: layers
        ListElement { name: "Background"; image: "01.png"; enable: true }
    }

    Component {
        id: imgDelegate
        Image {
            source: image
            z: 1000 - index
            visible: enable
        }
    }
}


