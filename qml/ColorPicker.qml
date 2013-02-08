import QtQuick 2.0
import QtGraphicalEffects 1.0

Item {
    id: container
    width: 700
    height: 700
    Canvas {
        id: canvas
        //var canvasSide = min(container.width, container.width)
        //width: canvasSide
        //height: canvasSide
        onPaint: {
            var ctx = canvas.getContext("2d");
            var gradient = ctx.createConicalGradient(50, 50, 0.2);
            gradient.addColorStop(0, "red");
            gradient.addColorStop(1, "blue");
        }
    }


/*
    ConicalGradient {
        id: conicalGradient
        anchors.fill: parent
        angle: 90
*/
        /*
        gradient: Gradient {
            GradientStop {position: 0; color: "red"}
            GradientStop {position: 1; color: "blue"}
        }
        */


/*

        gradient: {

            //var x = 0.2
            //gradient.stops.position = x
            //console.log(gradient.stops.position)
            conicalGradient.gradient.stops.objectName = "stop"
            console.log(conicalGradient.gradient.stops.objectName)
        }
*/
/*
        gradient: {
            //id: conicalGradient
            var stepColor = 0
            var stepPosition = 0
            while (stepColor < 1) {
                //Gradient.stops.position = ste
                //conicalGradient.gradient.stops.position = stepPosition
                //conicalGradient.gradient.stops.color = Qt.hsla(stepColor, 1, 0.5, 1)
                //console.log(stepColor)
                GradientStop.position = stepPosition
                GradientStop.color = stepColor
                stepColor += 1 / 2
                stepPosition += 1 / 2
            }
        }
*/

}
