/* AprilBrush - Digital Painting Software
 * Copyright (C) 2012-2014 Vladimir Zarypov <krre31@gmail.com>
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

import QtQuick 2.4
import QtQuick.Dialogs 1.2

MessageDialog {
    title: qsTr("About AprilBrush")
    standardButtons: StandardButton.Ok
    text: "<h3>AprilBrush " + mainRoot.version + "</h3>
          Build date: " + coreLib.buildDate() + "<br>
          Copyright (c) 2012-2014, Vladimir Zarypov<br>
          <a href=\"http://sourceforge.net/projects/aprilbrush\">http://sourceforge.net/projects/aprilbrush</a>"
    Component.onCompleted: open()
}
