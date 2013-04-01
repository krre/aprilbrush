import QtQuick 2.0
import "components"

Window {
    id: root
    title: "Brush Settings"

    property int size
    property int opacityBrush
    property int spacing
    property int hardness
    property int roundness
    property int angle

    property alias brushSettingsModel: brushSettingsModel

    Item {
        anchors.fill: parent
        anchors.bottomMargin: 15

        ListView {
            id: brushSettingsView
            model: brushSettingsModel
            delegate: brushSettingsDelegate

            anchors.fill: parent
            orientation: ListView.Vertical
            spacing: 30
            clip: true
        }

        ListModel {
            id: brushSettingsModel
            ListElement { nameParam: "Size"; minParam: 1; maxParam: 200; initParam: 30 }
            ListElement { nameParam: "Opacity"; minParam: 0; maxParam: 100; initParam: 50 }
            ListElement { nameParam: "Spacing"; minParam: 1; maxParam: 100; initParam: 30 }
            ListElement { nameParam: "Hardness"; minParam: 1; maxParam: 100; initParam: 85 }
            ListElement { nameParam: "Roundness"; minParam: 1; maxParam: 10; initParam: 1 }
            ListElement { nameParam: "Angle"; minParam: 0; maxParam: 180; initParam: 90 }
        }

        Component {
            id: brushSettingsDelegate
            Item {
                width: parent.width
                Slider {
                    name: nameParam; min: minParam; max: maxParam; init: initParam
                    onValueChanged: {
                        if (name == "Size") size = value
                        if (name == "Opacity") opacityBrush = value
                        if (name == "Spacing") spacing = value
                        if (name == "Hardness") hardness = value
                        if (name == "Roundness") roundness = value
                        if (name == "Angle") angle = value
                    }
                }
            }
        }
    }
}

