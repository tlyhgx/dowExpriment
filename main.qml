import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.15
import QtQuick.Layouts 1.12
import "contents"

Window {
    width: 1204
    height: 768
    visible: true
    title: qsTr("陶氏实验数据监控系统v1.0")
    //    Rectangle{
    //        width: parent.width;
    //        height: parent.height;
    //        gradient: Gradient{
    //            GradientStop{position:0.0;color:"lightsteelblue"}
    //            GradientStop{position:1.0;color:"cyan"}
    //        }
    //    }



    WorkUI{

        x:300;
        y:60;
    }




    Rectangle{
        width: 420;
        height: 250;
        x:100;
        y:360;
        border.color: "black";
        border.width: 1
        Column{
            Label{
                text: "工作信息:"
            }
            //        EventList{}

            //            EventTableFromControl{}
            //            EventTableView{}
            EventTableEasyTable{}

        }

    }

    GridLayout {
        x:parent.width-300;
        y:parent.height-300;
        width: 120
        rows: 3
        columns: 2
        Label{
            text: "工作状态:"
        }
        Label{
            text: "停止"
        }
        Label{
            text: "实验名称:"
        }
        TextField {
            placeholderText: "实验名称"
            //            width: 50;
        }
        HwwButton{
            text: "启动"

        }
        HwwButton{
            text: "停止"
        }


    }

    Rectangle{

        width: 300;
        height: 80;
        x:parent.width-450;
        y:parent.height-100;
        Row{
            id: buttonRow
            spacing: 6
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 12
            width: parent.width


            HwwButton{
                width: 100;
                height: 30;
                text: "实时曲线"
            }
            HwwButton{
                width: 100;
                height: 30;
                text: "历史数据"
            }
            HwwButton{
                width: 100;
                height: 30;
                text: "参数设置"
            }
            HwwButton{
                width: 100;
                height: 30;
                text: "报警记录"
            }





        }
    }

}
