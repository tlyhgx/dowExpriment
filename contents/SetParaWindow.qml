import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
Window {
    title: qsTr("参数设置")
    height: 450
    width: 750

    Column{

        spacing: 2

        Row{
            Label{
                text: "数据记录周期(s)："

                font{
                    pixelSize: 18
                    bold: true
                }
                anchors.verticalCenter:  parent.verticalCenter

            }

            TextField {
                width:60
                id:recordRecycle_input;

                font{
                    pixelSize: 18
                    bold: true
                }
                selectByMouse: true
                horizontalAlignment: "AlignRight"

                Component.onCompleted: {
                    recordRecycle_input.text=setParaBackend.recordRecycle_s
                }
            }

        }

    }
    Row{
        x:300
        y:200
        Button{
            text: "保存"

            onClicked: {
                setParaBackend.recordRecycle_s=recordRecycle_input.text
            }
        }
        Button{
            text: "退出"
            onClicked: {
                setParaWindow.close()
            }

        }
    }

}
