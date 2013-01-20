import QtQuick 1.1
import Drawing 1.0

Rectangle {
    // Checker background
    Image {
        width: parent.width
        height: parent.height
        fillMode: Image.Tile
        source: "qrc:/svg/svg/checker.svg"
    }
    // White layer
    PaintSpace {
        color: "white"
    }
    // Transparent layer
    PaintSpace {

    }
}
