import QtQuick 1.1

Rectangle {
    color: "white"

    // Checker background
    Image {
        width: parent.width
        height: parent.height
        fillMode: Image.Tile
        source: "qrc:/svg/svg/checker.svg"
    }
}
