﻿import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.15
import QtQuick.Layouts 1.12

import "contents"


Window {
    id:mainWin

    property int  totalWidth: 1366
    property int  totalHeight: 768
    property int  firstLineHeight: 580
    property int  grid21Width: 500
    width: totalWidth
    height: totalHeight
    visible: true
    title: qsTr("陶氏实验数据监控系统v1.0")



    WorkUI{   //元器件及指示
        id:workUI
        x:0;y:10
        height: firstLineHeight
        width: totalWidth
        anchors.horizontalCenter: parent.horizontalCenter









    }
    HwwCanvas{  //
        x:0;y:0
        width: totalWidth
        height: totalHeight

    }
    Rectangle{  //工作信息
        width: grid21Width
        height: totalHeight-firstLineHeight
        x:30;y:workUI.height+20
        Column{
            Label{
                text: "工作信息:"
                font.pixelSize: 18
            }
            EventTableEasyTable{}
        }

    }
    Rectangle{   //启停等
        x:grid21Width+300;y:workUI.height+8
        width: 160
        Frame{

            Column{
                spacing: 5

                Rectangle{
                    width: 250;height: 120
                    GridLayout {
                        anchors.margins: 6
                        columnSpacing: 10
                        rowSpacing: 5


                        anchors.fill: parent
                        rows: 3
                        columns: 2
                        Label{
                            text: "工作状态:"
                            font{
                                pixelSize: 18
                                bold: true
                            }
                        }
                        Label{
                            text: "未记录!"  //TODO:还有个状态： 记录中...
                            font{
                                pixelSize: 18
                                bold: true
                            }
                        }
                        Label{
                            text: "实验名称:"
                            font{
                                pixelSize: 18
                                bold: true
                            }
                        }
                        TextField {
                            width:200
                            id:experiment_input;
                            placeholderText: "请输入实验名称!"
                            font{
                                pixelSize: 18
                                bold: true
                            }
                        }
                        Label{
                            text: "实验人员:"
                            font{
                                pixelSize: 18
                                bold: true
                            }
                        }
                        TextField {
                            id:operName_input
                            width:200
                            placeholderText: "请输入实验人员名字！"
                            font{
                                pixelSize: 18
                                bold: true
                            }
                        }

                    }
                }

                Row{
                    spacing: 100
                    width: 300;height: 30
                    leftPadding: 30


                    Rectangle{
                        anchors.leftMargin: 50
                        width: 60;height: 30
                        HwwButton{
                            id:start
                            text: "开始记录"
                            onClicked: {
                                //TODO1:
                                //记录操作员--记录实验名称--记录数据
                                mainBackend.operName=operName_input.text
                                mainBackend.exprimentName=experiment_input.text
                            console.log(operName_input.text)
                            }
                        }
                    }
                    Rectangle{
                        width: 60;height: 30
                        HwwButton{

                            text: "停止记录"
                        }

                    }
                }
            }
        }



    }

    Connections{
        target: mainBackend
        function onSignalValChanged(signalVals){

            console.log("数据传递成功！")

            workUI.velocityOfFlowVal=signalVals[0]
            workUI.velocityOfAirVal=signalVals[1]
            workUI.airPressVal=signalVals[2]
            workUI.rotationSpeedVal=signalVals[3]
            workUI.no1TempVal=signalVals[4].toFixed(1)
            workUI.no2TempVal=signalVals[5].toFixed(1)
            workUI.no3TempVal=signalVals[6].toFixed(1)
            workUI.no4TempVal=signalVals[7].toFixed(1)
            workUI.no5TempVal=signalVals[8].toFixed(1)

        }
    }

    Rectangle{     //其它窗口按钮组
        width: 120
        height: totalHeight-firstLineHeight
        x:totalWidth-width;y:workUI.height+8
        anchors.margins: 20

        Column{
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
                RealTimeCurveWindow{
                    id:realTimeCurveWindow
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        realTimeCurveWindow.show()
                    }
                }
            }
            HwwButton{
                width: 100;
                height: 30;
                text: "历史数据"
                HistroyDataWindow{
                    id:historyDataWindow

                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        historyDataWindow.show()
                    }
                }
            }
            HwwButton{
                width: 100;
                height: 30;
                text: "参数设置"
                SetParaWindow{
                    id:setParaWindow
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        setParaWindow.show()
                    }
                }

            }
            HwwButton{
                width: 100;
                height: 30;
                text: "过程记录"
                ProcessRecordWindow{
                    id:processRecordWindow
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        processRecordWindow.show()
                    }
                }
            }

            HwwButton{
                width: 100;
                height: 30;
                text: "退 出"
                ProcessRecordWindow{
                    id:exit
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        Qt.exit(0);
                    }
                }
            }
        }
    }



}
