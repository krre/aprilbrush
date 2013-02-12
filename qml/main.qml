import QtQuick 2.0
import QtQuick.Window 2.0
import Drawing 1.0

Rectangle {
    id: container
    width: 800
    height: 600
    signal createPixmap;

    MouseArea {
        anchors.fill: parent
        onPositionChanged: {
            console.log(mouse.x + " " + mouse.y)
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
        width: Screen.width
        height: Screen.height
        color: "white"
    }

    // Transparent layer
    PaintSpace {
        width: Screen.width
        height: Screen.height

    }

    // Files panel
    FilePanel {
        id: filePanel
        x: 0; y: 0
        onPressFileItem: {
            if (itemName == "New") {
                var numNextPage = zeroFill(pagePanel.pageModel.count + 1, 2)
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

    function zeroFill(number, width)
    {
        width -= number.toString().length;
        if (width > 0)
        {
            return new Array(width + (/\./.test(number) ? 2 : 1)).join('0') + number;
        }
        return number + ""; // always return a string
    }
}


