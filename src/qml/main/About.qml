import QtQuick 2.6
import "../components/messagedialog"

MessageDialogBase {
    title: qsTr(String("About %1").arg(Qt.application.name))
    text: String("<h3>%1 %2</h3>
          Based on Qt %3<br>
          Build on %4<br><br>
          Copyright © 2012-2016, Vladimir Zarypov<br>
          <a href=\"https://github.com/krre/aprilbrush\">
          https://github.com/krre/aprilbrush</a>").arg(Qt.application.name).arg(Qt.application.version).arg(Core.qtVersion).arg(Core.buildDate)
}
