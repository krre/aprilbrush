import QtQuick 2.0
import "components"

Window {
    id: root
    title: "Brush Settings"

    property alias size: sizeSlider
    property alias opaque: opacitySlider
    property alias spacing: spacingSlider
    property alias hardness: hardnessSlider
    property alias roundness: roundnessSlider
    property alias angle: angleSlider

    Item {
        id: sliders
        anchors.fill: parent
        anchors.bottomMargin: 15

        VisualItemModel {
            id: brushSettingsModel
            Slider { id: sizeSlider; width: sliders.width; name: "Size"; min: 1; max: 200 }
            Slider { id: opacitySlider; width: sliders.width; name: "Opacity"; min: 0; max: 100 }
            Slider { id: spacingSlider; width: sliders.width; name: "Spacing"; min: 1; max: 100 }
            Slider { id: hardnessSlider; width: sliders.width; name: "Hardness"; min: 1; max: 100 }
            Slider { id: roundnessSlider; width: sliders.width; name: "Roundness"; min: 1; max: 10 }
            Slider { id: angleSlider; width: sliders.width; name: "Angle"; min: 0; max: 180 }
        }

        ListView {
            model: brushSettingsModel
            anchors.fill: parent
            orientation: ListView.Vertical
            clip: true
        }
    }
}

