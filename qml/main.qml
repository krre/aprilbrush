import QtQuick 2.0
import QtQuick.Window 2.0
import Drawing 1.0
import BrushEngine 1.0
import "utils.js" as Util

Rectangle {
    id: container
    width: 800
    height: 600
    Keys.onDeletePressed: {brush.clear(); space.update()}
    focus: true

    MouseArea {
        anchors.fill: parent
        //hoverEnabled: true
        onPressed: {brush.paintDab(mouseX, mouseY); space.update()}
        onReleased: brush.setTouch(false)
        onPositionChanged: {
            brush.paintDab(mouseX, mouseY)
        }
    }

    // Checker background
    Image {
        width: Screen.width
        height: Screen.height
        fillMode: Image.Tile
        source: "../svg/checker.svg"
    }

    // White layer
    PaintSpace {
        id: space
        width: Screen.width
        height: Screen.height
        color: "white"
    }
/*
    // Transparent layer
    PaintSpace {
        width: Screen.width
        height: Screen.height
        color: "red"
    }
*/
    Brush {
        id: brush
        onPaintDone: space.update()
        size: 50
        spacing: 100
        hardness: 85
        color: "blue"
        opacity: 100
    }

    // Files panel
    FilePanel {
        id: filePanel
        x: 0; y: 0
        onPressFileItem: {
            if (itemName == "New") {
                var numNextPage = Util.zeroFill(pagePanel.pageModel.count + 1, 2)
                pagePanel.pageModel.append({"name": "Untitled " + numNextPage})
            }
        }
    }

    // Pages panel
    PagePanel
    {
        id: pagePanel
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width - filePanel.width * 2
    }   
}


