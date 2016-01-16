import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4
import QtQuick.LocalStorage 2.0
import "../components"
import "../../js/brush-lib.js" as BrushLib

Panel {
    property int currentBrush: 0
    id: root
    title: qsTr("Brush Library")
    objectName: "brushLibrary"

    Component.onCompleted: {
        loadBrushes()
    }

    function changeBrushSettings(row) {
        brushSettings.size = libraryModel.get(row).size
        brushSettings.opacity = libraryModel.get(row).opacity
        brushSettings.flow = libraryModel.get(row).flow
        brushSettings.spacing = libraryModel.get(row).spacing
        brushSettings.hardness = libraryModel.get(row).hardness
        brushSettings.roundness = libraryModel.get(row).roundness
        brushSettings.angle = libraryModel.get(row).angle
        brushSettings.jitter = libraryModel.get(row).jitter
        brushSettings.eraser = libraryModel.get(row).eraser
        currentBrush = row
    }

    function loadBrushes() {
        var db = LocalStorage.openDatabaseSync("Brush", "1.0", "Brush Pack", 1000000);

        db.transaction(
            function(tx) {
                tx.executeSql('CREATE TABLE IF NOT EXISTS Inner(name TEXT, size TEXT, opacity TEXT, flow TEXT, spacing TEXT, hardness TEXT, roundness TEXT, angle TEXT, jitter TEXT, eraser TEXT)')
                var rs = tx.executeSql('SELECT * FROM Inner');
                if (!rs.rows.length) {
                    tx.executeSql('INSERT INTO Inner VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?)', BrushLib.default1)
                    tx.executeSql('INSERT INTO Inner VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?)', BrushLib.big)
                    tx.executeSql('INSERT INTO Inner VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?)', BrushLib.little)
                    tx.executeSql('INSERT INTO Inner VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?)', BrushLib.hardEraser)
                    tx.executeSql('INSERT INTO Inner VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?)', BrushLib.sofrEraser)
                    rs = tx.executeSql('SELECT * FROM Inner')
                }

                for(var i = 0; i < rs.rows.length; i++) {
                    libraryModel.append({ name: rs.rows.item(i).name, size: rs.rows.item(i).size, opacity: rs.rows.item(i).opacity, flow: rs.rows.item(i).flow, spacing: rs.rows.item(i).spacing,
                                        hardness: rs.rows.item(i).hardness, roundness: rs.rows.item(i).roundness, angle: rs.rows.item(i).angle, jitter: rs.rows.item(i).jitter, eraser: rs.rows.item(i).eraser })
                }
            }
        )
    }

    Flow {
        anchors.fill: parent
        spacing: 5

        Repeater {
            model: libraryModel
            delegate: Button {
                width: 50
                height: 50
                text: name
                isDefault: index == currentBrush
                onClicked: changeBrushSettings(index)
                style: ButtonStyle {
                    label: Text {
                        text: control.text
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.WordWrap
                        elide: Text.ElideRight
                    }

                    background: Rectangle {
                        implicitWidth: 50
                        implicitHeight: 50
                        border.color: control.isDefault ? "red" : "#888"
                        radius: 4
                        antialiasing: true
                        gradient: Gradient {
                            GradientStop { position: 0 ; color: control.pressed ? "#ccc" : "#eee" }
                            GradientStop { position: 1 ; color: control.pressed ? "#aaa" : "#ccc" }
                        }
                    }
                }
            }
        }

        ListModel {
            id: libraryModel
        }
    }
}
