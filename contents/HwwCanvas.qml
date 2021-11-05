import QtQuick 2.15


Canvas{
    id:canvas
    property int  totalWidth: 1366
    property int  totalHeight: 768
    width: totalWidth
    height: totalHeight
    anchors.fill: parent
    onPaint: {
        var ctx=canvas.getContext("2d")
        ctx.beginPath()
        ctx.strokeStyle="lightblue"
        ctx.lineWidth=3
        ctx.moveTo(10,575)
        ctx.lineTo(1350,575)
        ctx.stroke()

    }

}
