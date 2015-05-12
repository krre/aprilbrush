import QtQuick 2.4
import QtQuick.Controls 1.3
import "components"
import "settings.js" as Settings
import "enums.js" as Enums

Panel {
    id: root
    title: qsTr("Brush Settings")
    property alias size: size.value
    property alias opaque: opaque.value
    property alias flow: flow.value
    property alias hardness: hardness.value
    property alias spacing: spacing.value
    property alias roundness: roundness.value
    property alias angle: angle.value
    property alias jitter: jitter.value
    property alias eraser: eraser.value
    objectName: "brushSettings"
    storage: ["size", "opaque", "flow", "hardness", "spacing", "roundness", "angle", "jitter", "eraser"]

    onSizeChanged: coreLib.setCursorShape(Enums.CanvasPaint, size.value)

    ScrollView {
        id: scrollView
        anchors.fill: parent

        ListView {
            clip: true
            spacing: 10

            model: VisualItemModel {
                id: brushModel
                property real sliderWidth: scrollView.width !== scrollView.viewport.width ? scrollView.viewport.width - 5 : scrollView.width
                SliderText { id: size; title: qsTr("Size"); width: brushModel.sliderWidth; minimumValue: 1; maximumValue: 100; value: 20 }
                SliderText { id: opaque; title: qsTr("Opacity"); width: brushModel.sliderWidth; value: 85 }
                SliderText { id: flow; title: qsTr("Flow"); width: brushModel.sliderWidth; value: 50 }
                SliderText { id: hardness; title: qsTr("Hardness"); width: brushModel.sliderWidth; minimumValue: 1; value: 95 }
                SliderText { id: spacing; title: qsTr("Spacing"); width: brushModel.sliderWidth; minimumValue: 5; maximumValue: 200; value: 25 }
                SliderText { id: roundness; title: qsTr("Roundness"); width: brushModel.sliderWidth; minimumValue: 1; maximumValue: 100; value: 100 }
                SliderText { id: angle; title: qsTr("Angle"); width: brushModel.sliderWidth; minimumValue: 0; maximumValue: 180; value: 0 }
                SliderText { id: jitter; title: qsTr("Jitter"); width: brushModel.sliderWidth; minimumValue: 0; maximumValue: 500; value: 0 }
                SliderText { id: eraser; title: qsTr("Eraser"); width: brushModel.sliderWidth; minimumValue: 0; maximumValue: 100; value: 0 }
            }
        }
    }
}

