import QtQuick 2.12
import QtQuick.Controls 2.12

Item{
    width: 300
    height: 400
    Canvas{
        id:canvas
        anchors.fill: parent
        onPaint: {
        var ctx=getContext("2d");
            ctx.fillStyle="lightgrey"
            ctx.strokeStyle="blue"
            ctx.lineWidth=4
            ctx.lineJoin="round"

            ctx.fillRect(20,20,160,160)
            ctx.clearRect(30,30,140,140)
            ctx.strokeRect(20,20,80,80)

            ctx.fillStyle="lightblue"
            ctx.fillRect(10,10,50,50)

            ctx.fillStyle=ctx.createPattern("red",Qt.Dense1Pattern)
            ctx.fillRect(70,30,50,80)

            ctx.fillStyle="green"
            ctx.strokeStyle="blue"
            ctx.lineWidth=2
            ctx.font="bold 50px Arial"

            var text="崇峻科技"
            context.fillText(text,10,80)
            context.strokeText(text,10,150)
        }
    }
}
