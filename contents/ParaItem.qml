import QtQuick 2.0
import QtQuick.Controls 2.12
Item {
    id:paraItem
    property string paraName: "参数名称"
    property real currentVal_dis:0
    property string unit_dis: "单位"
    property string inputVal: recordCycle_input.text
    property alias nowVal: currentVal.text


    Row{
        spacing: 10
        Label{
            text: paraName
            width: 140
            font{
                pixelSize: 18
                bold: true
            }
            anchors.verticalCenter:  parent.verticalCenter
        }

        Label{
            width: 30
            id:currentVal
            font{
                pixelSize: 18
                bold: true
            }
            anchors.verticalCenter:  parent.verticalCenter
            horizontalAlignment: Text.AlignRight
            Component.onCompleted: {
                currentVal.text=currentVal_dis
            }
        }

        TextField {

            width:70
            height: 28
            anchors.leftMargin: 10
            id:recordCycle_input;
            font{
                pixelSize: 18
                bold: true
            }
            //            text: changedVal
            selectByMouse: true
            horizontalAlignment: "AlignRight"
            verticalAlignment: "AlignBottom"
        }

        Label{

            id:unit
            font{
                pixelSize: 18
                bold: true
            }
            anchors.verticalCenter:  parent.verticalCenter

            text: unit_dis
        }
    }
}
