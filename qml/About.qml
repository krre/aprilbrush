import QtQuick 2.0
import "components"

Window {
    title: ""
    defaultWidth: 420
    defaultHeight: 420

    Column {
        width: 200
        anchors.centerIn: parent
        height: parent.height
        spacing: 5

        Text {
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            text: "AprilBrush 0.1.0"
            font.pixelSize: 17
        }

        Text {
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            text: "Build date: 06 Apr 2013"
            font.pixelSize: 12
        }
        Text {
            width: parent.width
            text: "Copyright (c) 2012-2013, Vladimir Zarypov<br />Ukraine, Kiev<br /> \
                http://sourceforge.net/projects/aprilbrush<br />"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 12
        }
        Text {
           width: parent.width
           text: "Hotkeys"
           horizontalAlignment: Text.AlignHCenter
           font.pixelSize: 14
        }
        Row {
           width: parent.width
           Text {
               id: hotkeyList
               width: 120
               font.pixelSize: 12
               text: "Alt<br />
                      Space+Click<br />
                      Ctrl+Click<br />
                      B<br />
                      E<br />
                      Delete<br />
                      +<br />
                      -<br />
                      0<br />
                      F<br />
                      R<br />
                      I<br />
                      Ctrl+Z<br />
                      Ctrl+Y<br />
                      Ctrl+S<br / >
                      Ctrl+O<br />
                      Ctrl+E<br />"
           }
           Text {
               width: parent.width - hotkeyList.width
               font.pixelSize: 12
               text: "Dock Menu<br />
                      Pan<br />
                      Pick Color<br />
                      Brush<br />
                      Eraser<br />
                      Clear<br />
                      Zoom In<br />
                      Zoom Out<br />
                      Reset<br />
                      Mirror<br />
                      Rotate<br />
                      Fill Color<br />
                      Undo<br />
                      Redo<br />
                      Save<br />
                      Open<br />
                      Export<br />"
           }

        }
    }

    Component.onCompleted: {
        x = (parent.width - width) / 2
        y = (parent.height - height) / 2
    }

}
