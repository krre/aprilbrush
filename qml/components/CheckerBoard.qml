import QtQuick 2.0

Item {
    id: root
    property int cellSide: 10
    width: 100
    height: 100

    Rectangle {
    id: rect
    anchors.fill: parent

        Grid {
            id: grid
            anchors.fill: parent
            rows: parent.height / cellSide + (index%2 == 0 ? 2 : 1)
            columns: parent.width / cellSide + (index%2 == 0 ? 2 : 1)
            clip: true
            Repeater {
                model: grid.columns * grid.rows
                Rectangle {
                    width: root.cellSide
                    height: root.cellSide
                    color: (index%2 == 0) ? "gray" : "white"
                }
            }
        }
    }
    Shadow {
        surface: rect
    }
}



