import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import "contents"
Window {
    id:logoWin
    width: 480
    height: 500
    visible: true
    flags: Qt.FramelessWindowHint
    Rectangle{
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: "azure" }
            GradientStop { position: 1.0; color: "white" }
        }

        Column{

            anchors.fill:parent
            Label{
                padding: 30
                width: parent.width

                height: 40
                text: "欢迎使用实验监控系统"
                font{
                    pixelSize: 22
                }
            }
            Label{
                anchors.bottom: buttons.top
                padding: 20
                width: parent.width

                height: 40
                text: "重要提醒：一定要先给监控设备通电，再打开此软件！"
                color: "red"
                font{
                    pixelSize: 16
                }
            }
            Row{
                id:buttons
                padding: 25
                width: parent.width
                anchors.bottom: parent.bottom
                layoutDirection: Qt.RightToLeft
                spacing: 10
                HwwButton{
                    width: 100
                    height: 30
                    text: "退出"
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            Qt.exit(0)
                        }
                    }
                }
                HwwButton{
                    width: 100
                    height: 30
                    text: "确认"

                    MainWindow{
                        id:mainWindow
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            logoWin.close()
                            mainWindow.show()
                        }
                    }
                }

            }

        }
    }

}
