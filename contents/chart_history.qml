import QtQuick 2.0
import QtCharts 2.15
import QtQuick.Controls 2.15
import backend_history_chart 1.0
Item {
    id:top_level
    width:1680;height: 800

    //鼠标按下并保持标记
    property var  isPressed: false
    property var x_position: 0

    Backend_history_chart{
        id:backend_history_chart
        onOperNameChanged: {
            comboBox_experimentNames.model=backend_history_chart.experimentNames
        }

        //根据提交内容设定最值（两端放大10%）
        onDisplayValueScopeChanged:{
            if(backend_history_chart.displayValueScope.length===2){
                valueTemAxisY.min=backend_history_chart.displayValueScope[0]
                valueTemAxisY.max=backend_history_chart.displayValueScope[1]
                //                console.log(valueTemAxisY.min)
                //                console.log(valueTemAxisY.max)
            }

        }
        //根据提交内容设定时间段
        onTime_start_endChanged:{
            if(backend_history_chart.time_start_end.length===2)
            {
                x_axis.min=backend_history_chart.time_start_end[0]
                x_axis.max=backend_history_chart.time_start_end[1]
                //                console.log(x_axis.min)
                //                console.log(x_axis.max)
            }
            //            console.log("时间范围")
        }
        //显示全部内容
        onRecieveTimeAndValChanged: {
            analogValSeries.clear()
            for(var i=0;i<(backend_history_chart.recieveTimeAndVal.length);i=i+2)
            {
                //                console.log(backend_history_chart.recieveTimeAndVal[i])
                //                console.log(backend_history_chart.recieveTimeAndVal[i+1])
                analogValSeries.append(backend_history_chart.recieveTimeAndVal[i]
                                       ,backend_history_chart.recieveTimeAndVal[i+1])
            }


        }
    }

    ChartView{
        id:charView
        width: top_level.width
        height: top_level.height-100
        title: "历 史 曲 线"
        titleFont.pointSize:  22
        titleColor: "steelblue"



        //是否反锯齿化
        antialiasing: true


        ValueAxis{
            id: valueTemAxisY
            min: 0
            max: 5000
        }

        DateTimeAxis {
            id:x_axis
            format: "hh:mm:ss"
            tickCount: 20
//            labelsAngle: 45
//            titleFont.pixelSize: 8
//            titleFont.bold: true



        }

        SplineSeries{
            id:analogValSeries
            axisX: x_axis
            axisY:valueTemAxisY
            pointsVisible: true
            pointLabelsVisible: false
            useOpenGL: true

            // 显示提示框，根据x_坐标显示y值
            onHovered:  {
                //                console.log("显示")
                var p = charView.mapToPosition(point)
                var text = qsTr("%1").arg(point.y)
                id_tooltip.x = p.x
                id_tooltip.y = p.y - id_tooltip.height
                id_tooltip.text = text
                id_tooltip.visible = true
                //                console.log(p.x)
                //                console.log(p.y)
            }



        }
        //滚轮转动，左右移动
        MouseArea {
            anchors.fill: charView

            onWheel: {

                //滚轮转动，起止时间缩放
                if (wheel.angleDelta.y > 0) {
                    //x_axis,日期间隔加大
                    x_axis.min=new Date(x_axis.min.valueOf()-60*1000)
                    x_axis.max=new Date(x_axis.max.valueOf()+60*1000)

                }
                else {
                    x_axis.min=new Date(x_axis.min.valueOf()+60*1000)
                    x_axis.max=new Date(x_axis.max.valueOf()-60*1000)
                    //x_axis,日期间隔减少
                }


            }

            //鼠标左键按下时，左右移动，移动X轴坐标(时间)
            onPressAndHold: {
                x_axis.min=new Date(x_axis.min.valueOf()-60*1000)
                isPressed=true
            }

            onReleased: {
                isPressed=false
            }

            onMouseXChanged: {

                if(isPressed===true && x_position-mouseX<0)
                {
                    x_axis.min=new Date(x_axis.min.valueOf()-60*1000)
                    x_axis.max=new Date(x_axis.max.valueOf()-60*1000)
                }else if(isPressed===true && x_position-mouseX>0){
                    x_axis.min=new Date(x_axis.min.valueOf()+60*1000)
                    x_axis.max=new Date(x_axis.max.valueOf()+60*1000)
                }
                x_position=mouseX

            }



        }
        //y值显示提示框
        ToolTip {
            id: id_tooltip
            contentItem: Text{
                color: "#21be2b"
                text: id_tooltip.text
            }
            background: Rectangle {
                border.color: "#21be2b"
            }
        }

    }


    //操作人员实验名称、模拟量通道 combobox
    Row{
        id:selectItems
        anchors.horizontalCenter: parent.horizontalCenter
        y:charView.height+20
        spacing: 20
        //操作人员组
        Row{
            spacing: 5
            Label{
                text: "实验人员"
                font.pixelSize: 18
                anchors.verticalCenter:  parent.verticalCenter
            }
            ComboBox{
                //实验人员
                model: backend_history_chart.operNames

                onActivated: {
                    backend_history_chart.operName=currentText
                    //                    console.log(currentText)
                }
                onHighlighted: {
                model=backend_history_chart.operNames
                }

            }
        }
        //实验名称组
        Row{
            spacing: 5
            Label{
                text: "实验名称"
                font.pixelSize: 18
                anchors.verticalCenter:  parent.verticalCenter
            }
            ComboBox{
                id:comboBox_experimentNames
                width: 260
//                onHighlighted: {
////                model=backend_history_chart.experimentNames
//                }
            }

        }

        //显示的模拟量选择组
        Row{
            spacing: 5
            Label{
                text: "数值项"
                font.pixelSize: 18
                anchors.verticalCenter:  parent.verticalCenter
            }
            ComboBox{
                id:selectItem_analog
                model: ListModel{
                    ListElement{text:"1#温度"}
                    ListElement{text:"2#温度"}
                    ListElement{text:"3#温度"}
                    ListElement{text:"4#温度"}
                    ListElement{text:"5#温度"}
                    ListElement{text:"气体流量"}
                    ListElement{text:"气体压力"}
                    ListElement{text:"液体流量"}
                    ListElement{text:"搅拌转速"}
                }
            }
        }

        HwwButton{
            text: "确定"
            onClicked: {
                var current_sirialsName=selectItem_analog.currentText
                //曲线单位改为对应单位
                if((current_sirialsName==="1#温度")||(current_sirialsName==="2#温度")
                        ||(current_sirialsName==="3#温度")||(current_sirialsName==="4#温度")
                        ||(current_sirialsName==="5#温度"))
                {current_sirialsName=current_sirialsName+"(℃)"}
                else if(current_sirialsName==="气体流量")
                {current_sirialsName=current_sirialsName+"(SLPM)"}
                else if(current_sirialsName==="气体压力")
                {current_sirialsName=current_sirialsName+"(kPa)"}
                else if(current_sirialsName==="液体流量")
                {current_sirialsName=current_sirialsName+"(L/min)"}
                else if(current_sirialsName==="搅拌转速")
                {current_sirialsName=current_sirialsName+"(r/min)"}
                //                console.log(current_sirialsName)
                //曲线名称改为所选项
                analogValSeries.name=current_sirialsName

                if(comboBox_experimentNames.currentText!=='')
                {

                    //把comboBox的值传递到backend
                    backend_history_chart.analogName=selectItem_analog.currentText
                    backend_history_chart.experimentName=comboBox_experimentNames.currentText
                    //                    console.log("读取数据")
                    //查询数据
                    backend_history_chart.ask_datas_from_db()
                }

            }
        }


    }



    //提示
    Column{
        x:30
        y:top_level.height-20
        Label{
            text: "时间范围缩放：转动鼠标滚轮"
            font{
                pixelSize: 16
            }
            color: "cadetblue"
        }
        Label{
            text: "时间左右移动:鼠标左键按下，并保持1秒，然后左右移动"
            font{
                pixelSize: 16
            }
            color: "cadetblue"
        }
        Label{
            text:"显示某个时间点的值:移动鼠标到该点"
            font{
                pixelSize: 16
            }
            color: "cadetblue"
        }
    }




}
