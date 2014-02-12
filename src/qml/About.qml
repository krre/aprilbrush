/* AprilBrush - Digital Painting Software
 * Copyright (C) 2012-2013 Vladimir Zarypov <krre31@gmail.com>
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

import QtQuick 2.1
import QtQuick.Window 2.0
import QtQuick.Layouts 1.1

Window {
    title: qsTr("About " + mainRoot.appName)
    width: 450
    height: 500
    visible: true

    Component.onCompleted: {
        x = (Screen.width - width) / 2
        y = (Screen.height - height) / 2
    }

    onVisibleChanged: if (!visible) { destroy() }

    Text {
        anchors.centerIn: parent
        font.pointSize: 10
        textFormat: Text.RichText
        onLinkActivated: console.log(link)
        text: "<h3>" + mainRoot.appName + " " + mainRoot.version + "</h3><br>
              Build date: " + coreLib.buildDate() + "<br>
              Copyright (c) 2012-2014, Vladimir Zarypov<br>
              <a href=\"http://sourceforge.net/projects/aprilbrush\">http://sourceforge.net/projects/aprilbrush</a><br><br>
              <b>Hotkeys:</b><br>
              <table>
                  <tr><td>Space+Drag</td><td>Pan Canvas</td></tr>
                  <tr><td>Ctrl+Click</td><td>Pick Color</td></tr>
                  <tr><td>B</td><td>Brush</td></tr>
                  <tr><td>E</td><td>Eraser</td></tr>
                  <tr><td>Delete</td><td>Clear Canvas</td></tr>
                  <tr><td>+</td><td>Zoom In</td></tr>
                  <tr><td>-</td><td>Zoom Out</td></tr>
                  <tr><td>0</td><td>Reset Transformations</td></tr>
                  <tr><td>M</td><td>Mirror Canvas</td></tr>
                  <tr><td>R</td><td>Rotate Canvas</td></tr>
                  <tr><td>F</td><td>Fill Color</td></tr>
                  <tr><td>Z</td><td>Undo Command</td></tr>
                  <tr><td>X</td><td>Redo Command</td></tr>
                  <tr><td>Ctrl+O</td><td>Open File</td></tr>
                  <tr><td>Ctrl+S</td><td>Save File</td></tr>
                  <tr><td>Ctrl+Shift+S\n</td><td>Save As File</td></tr>
                  <tr><td>Ctrl+E</td><td>Export File</td></tr>
              </table>"
    }
}
