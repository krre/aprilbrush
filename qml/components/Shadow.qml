import QtQuick 2.0
import QtGraphicalEffects 1.0

DropShadow {
    property variant surface: null

    anchors.fill: surface
    horizontalOffset: 4
    verticalOffset: 4
    radius: 1
    samples: 7
    color: "#60000000"
    source: surface
}
