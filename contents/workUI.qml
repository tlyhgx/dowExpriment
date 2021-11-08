import QtQuick 2.0
import "../contents"
import QtQuick.Layouts 1.15
Item {
    id:workUI;
    width: 720;
    height: 460;
    property int  leftDeviceX: 360  //图左边元器件图的基础坐标x
    property int  leftDeviceValPosx: 240 //左边元器件数据指示的基础坐标x
    property int  tempPosX: 865    //温度指示基础坐标x
    property int  tempPosY: 90    //温度指示基础坐标y

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
//                    width: 40;
//                    height:50;
                    source: "../imgs/wendubiansongqi.png"
                    fillMode: Image.PreserveAspectFit
                }
            }


        }




    }

    Rectangle{ //文本
        anchors.fill: parent
        z:-1
        InfoLabel{
            id:airPress
            x:760;y:50
            deviceName: "气压"
            value: 2.2
            unit:"kpa"
        }
        InfoLabel{
            id:no1Temp
            x:tempPosX;y:tempPosY
            deviceName: "1号温度"
            value: 42.2
        }
        InfoLabel{
            id:no2Temp
            x:tempPosX+100;y:tempPosY
            deviceName: "2号温度"
            value: 63.8
        }
        InfoLabel{
            id:no3Temp
            x:tempPosX+200;y:tempPosY
            deviceName: "3号温度"
            value: 21.8
        }
        InfoLabel{
            id:no4Temp
            x:tempPosX+300;y:tempPosY
            deviceName: "4号温度"
            value: 111.2
        }
        InfoLabel{
            id:no5Temp
            x:tempPosX+400;y:tempPosY
            deviceName: "5号温度"
            value: 61.3
        }
        InfoLabel{
            id:rotationSpeed
            x:540;y:100
            deviceName: "转速"
            value: 120
            unit:"r/min"
        }
        InfoLabel{
            id:velocityOfFlow
            x:leftDeviceValPosx;y:125
            deviceName: "液体流速"
            value: 35
            unit:"l/min"
        }
        InfoLabel{
            id:velocityOfAir
            x:leftDeviceValPosx;y:240
            deviceName: "气体流速"
            value: 35
            unit:"l/min"
        }

        InfoLabel{
            id:pump1
            x:leftDeviceValPosx;y:330
            deviceName: "蠕动泵1"
            value: 1
            unit:"On"
        }
        InfoLabel{
            id:pump2
            x:leftDeviceValPosx;y:400
            deviceName: "蠕动泵2"
            value: 0
            unit:"Off"
        }


    }




}
