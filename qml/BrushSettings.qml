import QtQuick 2.0
import "components"

Window {
    title: "Brush Settings"

    property int size: sizeCtrl.value
    property int spacing: spacingCtrl.value
    property int hardness: hardnessCtrl.value
    property int opacity_: opacityCtrl.value
    property int roundness: roundnessCtrl.value
    property int angle: angleCtrl.value

    Column {
        width: parent.width
        spacing: 5
        Slider {id: sizeCtrl; name: "Size"; min: 1; max: 200; init: 30}
        Slider {id: spacingCtrl; name: "Spacing"; min: 1; max: 100; init: 30}
        Slider {id: opacityCtrl; name: "Opacity"; min: 0; max: 100; init: 50}
        Slider {id: hardnessCtrl; name: "Hardness"; min: 1; max: 100; init: 85}
        Slider {id: roundnessCtrl; name: "Roundness"; min: 1; max: 10; init: 1}
        Slider {id: angleCtrl; name: "Angle"; min: 0; max: 180; init: 90}
    }
}

