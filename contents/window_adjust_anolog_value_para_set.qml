import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
Item {
    height: 500;width: 680


    Label{
        y:30
        text: "温 度 修 正"
        font.pixelSize: 34
        font.bold:  true
        color: "deepskyblue"
        anchors.horizontalCenter:  parent.horizontalCenter
    }


    //温度修改输入框组
    GridLayout{
        columns: 2
        y:100
        anchors.horizontalCenter:  parent.horizontalCenter
        columnSpacing: 80
        rowSpacing: 40
        Group_label_textinput{
            width: 200;height: 30
            id:temp_adjust_input
            paraName: qsTr("1号温度修正(℃)")

        }
        Group_label_textinput{
            width: 200;height: 30
            id:temp_adjust_input2
            paraName: qsTr("2号温度修正(℃)")

        }
        Group_label_textinput{
            width: 200;height: 30
            id:temp_adjust_input3
            paraName: qsTr("3号温度修正(℃)")

        }
        Group_label_textinput{
            width: 200;height: 30
            id:temp_adjust_input4
            paraName: qsTr("4号温度修正(℃)")

        }
        Group_label_textinput{
            width: 200;height: 30
            id:temp_adjust_input5
            paraName: qsTr("5号温度修正(℃)")

        }





    }


    //提示
    Label{
    anchors.horizontalCenter:  parent.horizontalCenter
    y:parent.height-120
    text: "示例：当前实际温度为20℃，采集显示为21.6℃，则在对应输入框输入 -1.6；默认空为不修改。"
    color: "orange"
    font.pixelSize: 15
    }

    //确定、退出按钮组
    Row{
    x:parent.width-200
    y:parent.height-50
    spacing: 20
    HwwButton{
    text: "确 定"
    }
    HwwButton{
    text: "退 出"
    }
    }

}
