import QtQuick 1.1
//import Drawing 1.0

Rectangle {
    ListModel {
        id: pageModel

        ListElement {
            name: "Untitled 01"
        }

    }

    Component {
        id: pageDelegate
        Rectangle {
            //clip: true
            height: listView.height
            width: 70
            color: "black"
            Text {
                text: name
                anchors.centerIn: parent
                color: "white"
                font.bold: true
            }
        }
    }

    // Checker background
    Image {
        width: parent.width
        height: parent.height
        fillMode: Image.Tile
        source: "qrc:/svg/svg/checker.svg"
    }

    Rectangle {
        id: tabWidget
        property int tabWidth: pageModel.count * 70 + 50
        width: tabWidth < 700 ? tabWidth : 700
        height: 30
        smooth: true
        anchors.horizontalCenter: parent.horizontalCenter

        Row {
            width: parent.width
            height: parent.height
            Rectangle {
                width: 50
                height: parent.height
                color: "red"
                Text {
                    text: "New"
                    anchors.centerIn: parent
                    color: "white"
                    font.bold: true
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        var numNextPage = zeroFill(pageModel.count + 1, 2)
                        pageModel.append({"name": "Untitled " + numNextPage})
                    }
                }
            }

            ListView {
                id: listView
                model: pageModel
                delegate: pageDelegate

                orientation: ListView.Horizontal
                spacing: 10
                width: pageModel.count * 70
                height: parent.height
                anchors.margins: 5
            }

        }
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

