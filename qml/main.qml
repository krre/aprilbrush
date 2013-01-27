import QtQuick 1.1
import Drawing 1.0

Rectangle {
    id: container
    width: 800
    height: 600

    // Checker background
    Image {
        width: parent.width
        height: parent.height
        fillMode: Image.Tile
        source: "qrc:/svg/svg/checker.svg"
    }   
/*
    // White layer
    PaintSpace {
        color: "white"
    }
    // Transparent layer
    PaintSpace {

    }
*/
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


