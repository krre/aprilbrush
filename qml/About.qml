/* AprilBrush - Digital Painting Software
 * Copyright (C) 2012-2013 Vladimir Zarypov <krre@mail.ru>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

import QtQuick 2.0
import "components"

Window {
    title: ""
    defaultWidth: 420
    defaultHeight: 450

    Column {
        width: 200
        anchors.centerIn: parent
        height: parent.height
        spacing: 5

        Text {
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            text: main.version
            font.pixelSize: 17
        }

        Text {
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            text: "Build date: " + coreLib.buildDate()
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
               text: "C<br />
                      Space+Drag<br />
                      Ctrl+Click<br />
                      B<br />
                      E<br />
                      Delete<br />
                      +<br />
                      -<br />
                      0<br />
                      M<br />
                      R<br />
                      F<br />
                      Z<br />
                      X<br />
                      Ctrl+S<br / >
                      Shift+S<br / >
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
                      Save As<br />
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
