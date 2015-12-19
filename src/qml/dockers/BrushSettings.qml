import QtQuick 2.6
import QtQuick.Controls 1.4
import "../components"
import "../../js/enums.js" as Enums

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

    Component.onDestruction: {
        for (var i = 0; i < brushModel.count; i++) {
            var slider = brushModel.children[i]
            Settings.setValue("Brush", slider.objectName, slider.value)
        }
    }

    onSizeChanged: {
        BrushEngine.size = size.value
        coreLib.setCursorShape(Enums.CanvasPaint, size.value)
    }

    onSpacingChanged: BrushEngine.spacing = spacing.value
    onHardnessChanged: BrushEngine.hardness = hardness.value
    onOpaqueChanged: BrushEngine.opacity = opaque.value
    onFlowChanged: BrushEngine.flow = flow.value
    onRoundnessChanged: BrushEngine.roundness = roundness.value
    onAngleChanged: BrushEngine.angle = angle.value
    onJitterChanged: BrushEngine.jitter = jitter.value
    onEraserChanged: BrushEngine.eraser = eraser.value

    ScrollView {
        id: scrollView
        anchors.fill: parent

        ListView {
            clip: true
            spacing: 10

            model: VisualItemModel {
                id: brushModel
                property real sliderWidth: scrollView.width !== scrollView.viewport.width ? scrollView.viewport.width - 5 : scrollView.width
                SliderText { id: size; objectName: "size"; title: qsTr("Size"); width: brushModel.sliderWidth; minimumValue: 1; maximumValue: 100; value: Settings.value("Brush", objectName, 30) }
                SliderText { id: opaque; objectName: "opacity"; title: qsTr("Opacity"); width: brushModel.sliderWidth; value: Settings.value("Brush", objectName, 85) }
                SliderText { id: flow; objectName: "flow"; title: qsTr("Flow"); width: brushModel.sliderWidth; value: Settings.value("Brush", objectName, 50) }
                SliderText { id: hardness; objectName: "hardness"; title: qsTr("Hardness"); width: brushModel.sliderWidth; minimumValue: 1; value: Settings.value("Brush", objectName, 95) }
                SliderText { id: spacing; objectName: "spacing"; title: qsTr("Spacing"); width: brushModel.sliderWidth; minimumValue: 5; maximumValue: 200; value: Settings.value("Brush", objectName, 25) }
                SliderText { id: roundness; objectName: "roundness"; title: qsTr("Roundness"); width: brushModel.sliderWidth; minimumValue: 1; maximumValue: 100; value: Settings.value("Brush", objectName, 100) }
                SliderText { id: angle; objectName: "angle"; title: qsTr("Angle"); width: brushModel.sliderWidth; minimumValue: 0; maximumValue: 180; value: Settings.value("Brush", objectName, 0) }
                SliderText { id: jitter; objectName: "jitter"; title: qsTr("Jitter"); width: brushModel.sliderWidth; minimumValue: 0; maximumValue: 500; value: Settings.value("Brush", objectName, 0) }
                SliderText { id: eraser; objectName: "eraser"; title: qsTr("Eraser"); width: brushModel.sliderWidth; minimumValue: 0; maximumValue: 100; value: Settings.value("Brush", objectName, 0) }
            }
        }
    }
}

