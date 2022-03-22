import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12
import backend_adjust_analog_set 1.0
Window {
    id:window_adjust_value
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
    Backend_adjust_analog_set{id:backend_adjust_val}
    //确定、退出按钮组
    Row{
        x:parent.width-200
        y:parent.height-50
        spacing: 20
        HwwButton{
            text: "确 定"
            onClicked: {


                //把数组传输到后台
                var input_adjust_vals=new Array
                var isChanged=false
                if(temp_adjust_input.setVal=="")
                {
                    input_adjust_vals[0]=0;
                }else{
                    input_adjust_vals[0]=temp_adjust_input.setVal;
                    isChanged=true
                }

                if(temp_adjust_input2.setVal=="")
                {
                    input_adjust_vals[1]=0;
                }else{
                    input_adjust_vals[1]=temp_adjust_input2.setVal;
                    isChanged=true
                }
                if(temp_adjust_input3.setVal=="")
                {
                    input_adjust_vals[2]=0;
                }else{
                    input_adjust_vals[2]=temp_adjust_input3.setVal;
                    isChanged=true
                }
                if(temp_adjust_input4.setVal=="")
                {
                    input_adjust_vals[3]=0;
                }else{
                    input_adjust_vals[3]=temp_adjust_input4.setVal;
                    isChanged=true
                }
                if(temp_adjust_input5.setVal=="")
                {
                    input_adjust_vals[4]=0;
                }else{
                    input_adjust_vals[4]=temp_adjust_input5.setVal;
                    isChanged=true
                }
//                    console.log(input_adjust_vals);

                if(isChanged===true){
                    backend_adjust_val.tem_vals=input_adjust_vals


                    //关闭窗口，以便重新打开后可读取修正值
                    window_adjust_value.close()
                }

            }
        }
        HwwButton{
            text: "退 出"
            onClicked: {
                window_adjust_value.hide()
            }

        }
    }

}
