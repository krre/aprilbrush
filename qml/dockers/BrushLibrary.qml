import QtQuick 2.5
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.3
import QtQuick.LocalStorage 2.0
import "../components"
import "../../js/settings.js" as Settings

Panel {
    id: root
    title: qsTr("Brush Library")
    objectName: "brushLibrary"

    Component.onCompleted: {
        loadBrushes()
        changeBrushSettings(0)
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
    }

    function loadBrushes() {
        var db = LocalStorage.openDatabaseSync("Brush", "1.0", "Brush Pack", 1000000);

        db.transaction(
            function(tx) {
                tx.executeSql('CREATE TABLE IF NOT EXISTS Inner(name TEXT, size TEXT, opacity TEXT, flow TEXT, spacing TEXT, hardness TEXT, roundness TEXT, angle TEXT, jitter TEXT, eraser TEXT)')
                var rs = tx.executeSql('SELECT * FROM Inner');
                if (!rs.rows.length) {
                    tx.executeSql('INSERT INTO Inner VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?)', [ 'Default', '30', '80', '100', '25', '85', '100', '0', '0', '0' ])
                    tx.executeSql('INSERT INTO Inner VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?)', [ 'Big', '100', '80', '100', '10', '85', '100', '0', '0', '0' ])
                    tx.executeSql('INSERT INTO Inner VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?)', [ 'Little', '5', '80', '50', '10', '50', '100', '0', '0', '0' ])
                    tx.executeSql('INSERT INTO Inner VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?)', [ 'Hard Eraser', '30', '100', '80', '10', '90', '100', '0', '0', '100' ])
                    tx.executeSql('INSERT INTO Inner VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?)', [ 'Soft Eraser', '30', '100', '15', '10', '70', '100', '0', '0', '100' ])
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
                onClicked: changeBrushSettings(index)
                style: ButtonStyle {
                    label: Text {
                        text: control.text
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.WordWrap
                        elide: Text.ElideRight
                    }
                }
            }
        }

        ListModel {
            id: libraryModel
        }
    }
}
