import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import "contents"
Window {
    id:logoWin
    width: 480
    height: 500
    visible: true
    color: "#00000000"
    flags: Qt.SplashScreen
//        flags: Qt.FramelessWindowHint
    Rectangle{
        anchors.fill: parent
        radius:8
        gradient: Gradient {
            GradientStop { position: 0.0; color: "azure" }
            GradientStop { position: 1.0; color: "white" }
        }


        Label{

            x:10;y:50
            width: parent.width

            height: 40
            text: "欢迎使用实验监控系统"
            font{
                pixelSize: 28
//                italic: true
                bold: true


            }

          color: "darkblue"
        }
        Label{
            x:20;y:parent.height-90
            width: parent.width
            height: 20
            text: "注意：请先给监控设备通电，再打开此软件！否则可能造成卡顿。"
            color: "red"
            font{
                pixelSize: 15
            }
        }


        //确认、退出按钮
        Row{
            id:buttons
            width: parent.width
            x:parent.width-220
            y:parent.height-50

            rightPadding: 40
            spacing: 10

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
//                        mainWindow.raise()

                    }
                }
            }

            HwwButton{
                anchors.rightMargin: 10
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

        }




        //        ColumnLayout{

        //            anchors.fill:parent
        //            spacing: 20
        //            Label{
        //                Layout.alignment: Qt.AlignTop
        //                padding: 30
        //                width: parent.width

        //                height: 40
        //                text: "欢迎使用实验监控系统"
        //                font{
        //                    pixelSize: 26
        //                }
        //            }
        //            Label{
        //                Layout.leftMargin: 20
        //                Layout.alignment: Qt.AlignBottom
        //                width: parent.width
        //                height: 20
        //                text: "注意：请先给监控设备通电，再打开此软件！否则可能造成卡顿。"
        //                color: "red"
        //                font{
        //                    pixelSize: 16
        //                }
        //            }
        //            Row{
        //                id:buttons
        //                width: parent.width
        //                Layout.preferredHeight: 50
        //                Layout.alignment: Qt.AlignRight
        //                layoutDirection: Qt.RightToLeft
        //                spacing: 10
        //                HwwButton{
        //                    anchors.rightMargin: 10
        //                    width: 100
        //                    height: 30
        //                    text: "退出"
        //                    MouseArea{
        //                        anchors.fill: parent
        //                        onClicked: {
        //                            Qt.exit(0)
        //                        }
        //                    }
        //                }
        //                HwwButton{
        //                    width: 100
        //                    height: 30
        //                    text: "确认"

        //                    MainWindow{
        //                        id:mainWindow
        //                    }
        //                    MouseArea{
        //                        anchors.fill: parent
        //                        onClicked: {
        //                            logoWin.close()
        //                            mainWindow.show()
        ////                            mainWindow.visibility=Window.FullScreen
        //                        }
        //                    }
        //                }

        //            }

        //        }


    }

}
