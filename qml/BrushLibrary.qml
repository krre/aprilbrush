import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.3
import QtQuick.LocalStorage 2.0
import "components"
import "settings.js" as Settings

Panel {
    id: root
    title: qsTr("Brush Library")
    objectName: "brushLibrary"

    Component.onCompleted: {
//        loadBrushes()
        var brushPack = coreLib.loadBrushPack()
        var jsonBrushPack = JSON.parse(brushPack)
        for (var i = 0; i < jsonBrushPack.length; i++) {
            libraryModel.append(jsonBrushPack[i])
        }
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

//    function loadBrushes() {
//        var db = LocalStorage.openDatabaseSync("Brushes", "1.0", "Brush Pack", 1000000);

//        db.transaction(
//            function(tx) {
//                // Create the database if it doesn't already exist
//                tx.executeSql('CREATE TABLE IF NOT EXISTS Greeting(salutation TEXT, salutee TEXT)');

//                // Add (another) greeting row
//                tx.executeSql('INSERT INTO Greeting VALUES(?, ?)', [ 'hello', 'world' ]);

//                // Show all added greetings
//                var rs = tx.executeSql('SELECT * FROM Greeting');

//                var r = ""
//                for(var i = 0; i < rs.rows.length; i++) {
//                    r += rs.rows.item(i).salutation + ", " + rs.rows.item(i).salutee + "\n"
//                }
//                print(r)
//            }
//        )
//    }

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
