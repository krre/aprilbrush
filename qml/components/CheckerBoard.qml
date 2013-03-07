import QtQuick 2.0

Item {
    id: root
    property int cellSide: 30
    width: 100
    height: 100
    Grid {
        id: grid
        anchors.fill: parent
        rows: parent.height / cellSide
        columns: parent.width / cellSide
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

