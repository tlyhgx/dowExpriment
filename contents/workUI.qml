import QtQuick 2.0
import "../learn"
import QtQuick.Layouts 1.15
Item {
    id:workUI;
    width: 720;
    height: 460;
    property int  leftDeviceX: 360
    Rectangle{

        anchors.fill: parent
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
            x:950;
            y:150;
            spacing: 5
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






}
