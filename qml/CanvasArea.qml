import QtQuick 2.0

Item {
    id: root

    property color initColor: "white"
    property variant layersModel: layers

    width: 500
    height: 500

   /*


    Rectangle {
        anchors.fill: parent
        color: initColor
    }

    ListModel {
        id: layersModel
        ListElement {name: "Background"}
        ListElement {name: "Layer00"}
    }

    */

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
        ListElement { name: "img01"; image: "01.png"; depth: 50.0; enable: true }
        ListElement { name: "img02"; image: "02.png"; depth: 100.0; enable: true }
        ListElement { name: "img03"; image: "03.png"; depth: 30.0; enable: false }
    }

    Component {
        id: imgDelegate
        Image {
            source: image
            z: depth
            visible: enable
        }
    }


}


