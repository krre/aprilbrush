import QtQuick 2.0
import QtQuick.Window 2.0
import PaintItem 1.0

Item {
    id: root

    width: 500
    height: 500

    PathView {
        model: layersModel
        delegate: layersDelegate

        anchors.centerIn: parent
        path: Path {
            PathAttribute { name: "z"; value: 9999.0 }
            PathLine { x: 0; y: 0 }
            PathAttribute { name: "z"; value: 0.0 }
        }
    }

    Component {
        id: layersDelegate
        PaintSpace {
            width: root.width
            height: root.height
            contentsSize.width: Screen.width
            contentsSize.height: Screen.height
            hash: pagesModel.get(currentPage).hashPage * 1000 + hashLayer
            fillColor: colorImage
            z: 1000 - index
            visible: enable
        }
    }
}


