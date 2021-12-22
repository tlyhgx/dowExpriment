import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import "../main.qml"
Window {
    id:logo
    width: 450
    height: 600
    Column{
        anchors.centerIn: parent
        anchors.fill:parent
        Label{
            width: parent.width
            height: 40
            text: "欢迎使用实验监控系统"
        }
        Button{
            width: 100
            height: 30
            text: "确认"

            main{
                id:mainWindow
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    mainWindow.show()
                }
            }


        }
    }
}
