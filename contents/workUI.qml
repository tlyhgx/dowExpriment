import QtQuick 2.0
import "../contents"
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.12
Item {
    id:workUI;
    width: 1366;
    height: 580;
    property int  leftDeviceX: 360  //图左边元器件图的基础坐标x
    property int  leftDeviceValPosx: 240 //左边元器件数据指示的基础坐标x
    property int  tempPosX: 865    //温度指示基础坐标x
    property int  tempPosY: 90    //温度指示基础坐标y
    property real airPressVal: 0
    property real no1TempVal: 0
    property real  no2TempVal: 0
    property real  no3TempVal: 0
    property real  no4TempVal: 0
    property real  no5TempVal: 0
    property real  rotationSpeedVal: 0
    property real  velocityOfFlowVal: 0
    property real  velocityOfAirVal: 0

    property alias pump1State: pump1.value
    property alias  pump2State: pump2.value
    property alias heatState:heat.text
    property alias heatColor: heat.color

    Canvas{  //线
        id:canvas
        x:0;y:0

        anchors.fill: parent
        onPaint: {
            var ctx=canvas.getContext("2d")
            //底部横线
            ctx.strokeStyle="lightblue"
            ctx.beginPath()
            ctx.lineWidth=3
            ctx.moveTo(10,575)
            ctx.lineTo(1350,575)
            ctx.stroke()

            ctx.lineWidth=7
            ctx.strokeStyle="lightblue"

            //液体流量
            ctx.beginPath()
            ctx.moveTo(100,203)
            ctx.lineTo(600,203)
            ctx.stroke()

            //气体流量
            ctx.beginPath()
            ctx.moveTo(100,298)
            ctx.lineTo(600,298)
            ctx.stroke()


            //蠕动泵1
            ctx.beginPath()
            ctx.moveTo(100,391)
            ctx.lineTo(600,391)
            ctx.stroke()

            //蠕动泵2
            ctx.beginPath()
            ctx.moveTo(100,460)
            ctx.lineTo(600,460)
            ctx.stroke()

            //加热
            ctx.beginPath()
            ctx.moveTo(625,530)
            ctx.lineTo(815,530)
            ctx.lineTo(815,570)
            ctx.lineTo(625,570)
            ctx.closePath()
            ctx.stroke()


            ctx.lineWidth=3
            ctx.strokeStyle="#d566b6"
            ctx.setLineDash( [ 2, 1] )

            //温度1
            ctx.beginPath()
            ctx.moveTo(917,254)
            ctx.lineTo(917,280)
            ctx.lineTo(817,280)
            ctx.stroke()

            //温度2
            ctx.beginPath()
            ctx.moveTo(1015,254)
            ctx.lineTo(1015,300)
            ctx.lineTo(817,300)
            ctx.stroke()

            //温度3
            ctx.beginPath()
            ctx.moveTo(1113,254)
            ctx.lineTo(1113,320)
            ctx.lineTo(817,320)
            ctx.stroke()

            //温度4
            ctx.beginPath()
            ctx.moveTo(1211,254)
            ctx.lineTo(1211,340)
            ctx.lineTo(817,340)
            ctx.stroke()

            //温度5
            ctx.beginPath()
            ctx.moveTo(1309,254)
            ctx.lineTo(1309,360)
            ctx.lineTo(817,360)
            ctx.stroke()





        }

        Text {
            id: heat
            text: qsTr("未加热")
            x:696;y:540
            color: "blue"      //TODO1:
            font.pixelSize: 26
        }

    }


    Rectangle{  //图片

        anchors.fill: parent
        color: Qt.rgba(0,0,0,0)
        Image {
            id: tank
            source: "../imgs/pingdishaobei.png"
            width: 300;
            height:360;
            x:560;
            y:190;
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: mix
            source: "../imgs/mixer.png"
            width: 80;
            height:300;
            x:tank.x+tank.width/2-width/3;
            y:tank.y-200;
        }
        Image {
            id: qitiliuliang

            source: "../imgs/qitiliuliangji.png"
            width: 80;
            height:50;
            x:leftDeviceX;
            y:285;
        }
        Image {
            id: rudongbeng

            source: "../imgs/rudongbeng.png"
            width: 74;
            height:65;
            x:leftDeviceX;
            y:345;
            fillMode: Image.PreserveAspectFit
        }
        Image {
            id: rudongbeng2

            source: "../imgs/rudongbeng.png"
            width: 74;
            height:65;
            x:leftDeviceX;
            y:410;
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: yetiliuliang

            source: "../imgs/yetiliuliangji.png"
            width: 50;
            height:100;
            x:leftDeviceX;
            y:115;
        }
        Image {
            id: jiejinkaiguang

            source: "../imgs/jiejinkaigang.png"
            width: 40;
            height:70;
            x:630;
            y:125;

        }
        Image {
            id: yalibiansongqi

            source: "../imgs/yalibiansongqi.png"
            width: 20;
            height:70;
            x:800;
            y:110;

        }
        RowLayout{
            x:885;
            y:150;
            spacing: 18
            Repeater{

                model: 5
                Image {
                    id: wendubiansongqi

                    source: "../imgs/wendubiansongqi.png"
                    fillMode: Image.PreserveAspectFit
                }
            }


        }




    }

    Rectangle{ //文本
        id:textDis
        anchors.fill: parent
        z:-1
        InfoLabel{
            id:airPress
            x:760;y:50
            deviceName: "气压"
            value: airPressVal
            unit:"kpa"
        }
        InfoLabel{
            id:no1Temp
            x:tempPosX;y:tempPosY
            deviceName: "1号温度"
            value: no1TempVal
        }
        InfoLabel{
            id:no2Temp
            x:tempPosX+100;y:tempPosY
            deviceName: "2号温度"
            value: no2TempVal
        }
        InfoLabel{
            id:no3Temp
            x:tempPosX+200;y:tempPosY
            deviceName: "3号温度"
            value: no3TempVal
        }
        InfoLabel{
            id:no4Temp
            x:tempPosX+300;y:tempPosY
            deviceName: "4号温度"
            value: no4TempVal
        }
        InfoLabel{
            id:no5Temp
            x:tempPosX+400;y:tempPosY
            deviceName: "5号温度"
            value: no5TempVal
        }
        InfoLabel{
            id:rotationSpeed
            x:540;y:100
            deviceName: "转速"
            value: rotationSpeedVal
            unit:"r/min"
        }
        InfoLabel{
            id:velocityOfFlow
            x:leftDeviceValPosx;y:125
            deviceName: "液体流速"
            value: velocityOfFlowVal
            unit:"L/min"
        }
        InfoLabel{
            id:velocityOfAir
            x:leftDeviceValPosx;y:240
            deviceName: "气体流速"
            value: velocityOfAirVal
            unit:"SLPM"
        }

        InfoLabel{
            id:pump1
            x:leftDeviceValPosx;y:330
            deviceName: "蠕动泵1"
            value: "ON"
            unit:" "
        }
        InfoLabel{
            id:pump2
            x:leftDeviceValPosx;y:400
            deviceName: "蠕动泵2"
            value: "OFF"  //TODO1:
            unit:" "
        }


    }







    Label{  //显示坐标
        id:posDis
        x:0;y:0
        width: 60;height: 30
        color: "lightblue"
        text: "pos"


    }
    MouseArea{
        anchors.fill: parent
        onClicked: {
            posDis.text=mouseX+","+mouseY
        }
    }

}
