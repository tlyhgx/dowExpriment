import QtQuick 2.12

Item {
    width: 460
    height: 380
    Canvas{
        id:canvas
        anchors.fill: parent
        onPaint: {
            var ctx=getContext("2d");
            ctx.strokeStyle=Qt.rgba(0.1,0.1,0.1,0.2)
            //            ctx.strokeStyle="red"
            ctx.lineWidth=4

            ctx.beginPath()
            for(var i=0;i<5;i++)
            {
                ctx.rect(10+i*20,10+i*20,210-i*40,210-i*40);
                ctx.stroke();

            }

            for(var j=0;j<5;j++)
            {
                ctx.beginPath()
                ctx.rect(240+j*20,10+j*20,210-j*40,210-j*40);
                ctx.stroke();

            }
            ctx.strokeStyle="green"
            ctx.beginPath()
            ctx.moveTo(120,60)
            ctx.lineTo(20,180)
            ctx.lineTo(220,180)
            ctx.closePath()
            ctx.stroke()

            ctx.beginPath()
            ctx.moveTo(20,20)
            ctx.lineTo(100,20)
            ctx.arcTo(150,20,150,70,50)
            ctx.lineTo(150,120)
            ctx.stroke()

            var radial=ctx.createRadialGradient(30,70,5,60,50,80)
            radial.addColorStop(0,"white")
            radial.addColorStop(0.5,"#FF00FF")
            radial.addColorStop(1,"#333333")
            ctx.fillStyle=radial
            ctx.fillRect(10,10,100,100)
            ctx.strokeRect(10,10,100,100)

            onImageLoaded:{
                if(canvas.isImageError("http://www.baidu.com/img/bdlogo.gif"))
                {
                    console.log("Image failed to load!")
                }
                ctx.drawImage("http://www.baidu.com/img/bdlogo.gif",0,0,270,129)
            }
            ctx.strokeText("崇峻",30,40)
            ctx.translate(70,60)
            ctx.strokeText("崇峻",30,40)
        }

    }

    Component.onCompleted: {
    canvas.loadImage("http://www.baidu.com/img/bdlogo.gif")
    }
}
