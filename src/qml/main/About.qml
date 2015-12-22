import QtQuick 2.6
import QtQuick.Dialogs 1.2

MessageDialog {
    title: qsTr(String("About %1").arg(Qt.application.name))
    standardButtons: StandardButton.Ok
    text: String("<h3>%1 %2</h3>
          Based on Qt %3<br>
          Build on %4<br><br>
          Copyright (c) 2012-2015, Vladimir Zarypov<br>
          <a href=\"https://github.com/krre/aprilbrush\">
          https://github.com/krre/aprilbrush</a>").arg(Qt.application.name).arg(Qt.application.version).arg(coreLib.qtVersion).arg(coreLib.buildDate)
    Component.onCompleted: open()
    onVisibilityChanged: if (!visible) destroy()
}
