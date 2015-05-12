import QtQuick 2.4
import QtQuick.Dialogs 1.2

MessageDialog {
    title: qsTr("About AprilBrush")
    standardButtons: StandardButton.Ok
    text: "<h3>AprilBrush " + mainRoot.version + "</h3>
          Build date: " + coreLib.buildDate + "<br>
          Copyright (c) 2012-2015, Vladimir Zarypov<br>
          <a href=\"https://github.com/krre/aprilbrush-desktop\">https://github.com/krre/aprilbrush-desktop</a>"
    Component.onCompleted: open()
}
