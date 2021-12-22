import QtQuick 2.15
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
//        visibility: Window.FullScreen


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

    ListView{
        id:infoListView
        z:1
        width:grid21Width;height: totalHeight-firstLineHeight-10
        x:30;y:workUI.height+20
        model: infoListModel;
        //TODO:后添加的要显示在最上面
        //        verticalLayoutDirection:ItemView.BottomToTop
        header:Rectangle{
            width: infoListView.width
            height: 20

            Label{
                text: "事件信息："
                font.pixelSize: 18
                color: "darkblue"
            }
        }
        ScrollBar.vertical: ScrollBar{
            id:hbar

            hoverEnabled: true

            width: 20
            active: true
            anchors.right: parent.left

            background: Item{
                Rectangle{
                    anchors.centerIn: parent
                    height: parent.height
                    width: parent.width*0.2
                    color: 'grey'
                    radius: width/2
                }
            }
        }
        delegate: Text{
            required property string infoTime
            required property string infoContent
            text: infoTime+":  "+infoContent
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
                            id:workState
                            text: "未工作！"
                            //TODO:变化时，最好有颜色变化
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
                            text: "开始"
                            onClicked: {

                                //记录操作员--记录实验名称
                                workState.text="工作中..."
                                mainBackend.operName=operName_input.text
                                mainBackend.exprimentName=experiment_input.text
                                mainBackend.startSys()
                                //设置mainBackend属性willRec为true,是否记录的判断条件
                                mainBackend.willRec=true
                                //                                console.log(operName_input.text)
                            }
                        }
                    }
                    Rectangle{
                        width: 60;height: 30
                        HwwButton{

                            text: "停止"
                            onClicked: {
                                workState.text="未工作！"
                                //设置mainBackend属性willRec为false
                                mainBackend.willRec=false
                                mainBackend.stopSys()
                            }

                        }

                    }
                }
            }
        }



    }

    Connections{
        target: mainBackend
        function onOtherSignalValChanged(signalVals){

            //            console.log("数据传递成功！")
            workUI.velocityOfAirVal=signalVals[0].toFixed(1)
            workUI.airPressVal=signalVals[1].toFixed(1)
            workUI.rotationSpeedVal=signalVals[2].toFixed(1)
            workUI.velocityOfFlowVal=signalVals[3].toFixed(1)




        }
        function onTempSignalValChanged(tempSignalVals){
            workUI.no1TempVal=tempSignalVals[0].toFixed(1)
            workUI.no2TempVal=tempSignalVals[1].toFixed(1)
            workUI.no3TempVal=tempSignalVals[2].toFixed(1)
            workUI.no4TempVal=tempSignalVals[3].toFixed(1)
            workUI.no5TempVal=tempSignalVals[4].toFixed(1)
        }
        function onOutPutStateChanged(outPutStateVals){ //把输出状态赋值
           //TODO:搅拌转动效果
            if(outPutStateVals[0]==0)
            {workUI.heatState="未加热"
                workUI.heatColor="blue"}
            else if(outPutStateVals[0]==1)
            {workUI.heatState="加热中..."
                workUI.heatColor="red"}
            if(outPutStateVals[2]==1)
                workUI.pump1State="ON"
            else if(outPutStateVals[2]==0)
                workUI.pump1State="OFF"
            if(outPutStateVals[3]==1)
                workUI.pump2State="ON"
            else if(outPutStateVals[3]==0)
                workUI.pump2State="OFF"
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
                        mainBackend.stopSys()
                        exitTimer.start()
                    }
                }
            }

            Timer{
                id:exitTimer
                interval: 1000
                repeat: false
                triggeredOnStart: false
                onTriggered: {
                    Qt.exit(0);
                }
            }


        }
    }



}
