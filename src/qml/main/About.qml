import QtQuick 2.6
import QtQuick.Dialogs 1.2

MessageDialog {
    title: qsTr("About AprilBrush")
    standardButtons: StandardButton.Ok
    text: String("<h3>AprilBrush %1</h3>
          Based on Qt %2<br>
          Build on %3<br><br>
          Copyright (c) 2012-2015, Vladimir Zarypov<br>
          <a href=\"https://github.com/krre/aprilbrush\">
          https://github.com/krre/aprilbrush</a>").arg(mainRoot.version).arg(coreLib.qtVersion).arg(coreLib.buildDate)
    Component.onCompleted: open()
    onVisibilityChanged: if (!visible) destroy()
}
