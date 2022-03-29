import QtQuick 2.15
import QtQuick.Window 2.15
import QtCharts 2.15
import QtQuick.Controls 2.12




Window {

    property int  totalWidth: 1366
    property int  totalHeight: 768
    //后面循环时使用，定位
    property int  locate: 0
    property var timeArray: []
    //    visibility: Window.FullScreen
    width: totalWidth
    height: totalHeight
    flags: Qt.FramelessWindowHint
    title: qsTr("实时曲线")
    HwwButton{
        x:parent.width-100
        y:20
        z:1
        text: "退出"
        onClicked: {

            mainWindow.visible=true

            realTimeCurveWindow.hide()
        }
    }

    Rectangle{
        width: totalWidth
        height: totalHeight
        gradient: Gradient {
            GradientStop { position: 0.0; color: "lightblue" }
            GradientStop { position: 1.0; color: "white" }
        }



        ChartView {
            id: chartTempView
            height: parent.height / 4 * 2
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            legend.alignment: Qt.AlignLeft
            antialiasing: true


            Component.onCompleted: {
                timeScope()
            }



            ValueAxis{
                id: valueTemAxisY
                min: 0
                max: 200
                titleText: "Temperature [&deg;C]"
            }
            ValueAxis{
                id: valueTemAxisYRight
                min: 0
                max: 200
                titleText: "Temperature [&deg;C]"
            }

            DateTimeAxis {
                id:x_axis
                format: "hh:mm:ss"
                tickCount: 10
            }

            SplineSeries{
                id:tempSeries
                axisX: x_axis
                axisY:valueTemAxisY
                name:"1#温度"
            }
            SplineSeries {
                id: temp2Series
                axisX: x_axis
                axisYRight:  valueTemAxisYRight
                name: "2# 温度"
            }

            SplineSeries {
                id: temp3Series
                axisX: x_axis
                axisY: valueTemAxisY
                name: "3# 温度"
            }

            SplineSeries {
                id: temp4Series
                axisX: x_axis
                axisY: valueTemAxisY
                name: "4# 温度"
            }
            SplineSeries {
                id: temp5Series
                axisX: x_axis
                axisY: valueTemAxisY
                name: "5# 温度"
            }


        }



        ChartView {
            id: chartAirFlowView
            height: parent.height / 4
            width: parent.width
            anchors.top: chartTempView.bottom
            anchors.left: parent.left

            legend.alignment: Qt.AlignLeft
            antialiasing: true

            DateTimeAxis {
                id:x_axis_air
                format: "hh:mm:ss"
                tickCount: 10
                visible: false
            }
            ValueAxis{
                id: valueAirFlowAxisY
                min: 0.1
                max: 5
                titleText: "流量 slpm"
            }
            ValueAxis{
                id: valueAirPressAxisY
                min: -100
                max: 300
                titleText: "压力 kpa"
            }

            SplineSeries {
                id: airFlowSeries
                axisX: x_axis_air
                axisY: valueAirFlowAxisY
                name:"气体流量"
            }
            SplineSeries {
                id: airPressSeries
                axisX: x_axis_air
                axisYRight:  valueAirPressAxisY
                name:"气体压力"
            }

        }





        ChartView {
            id: chartOtherView
            height: parent.height / 4
            width: parent.width
            anchors.top: chartAirFlowView.bottom
            anchors.right: parent.right
            legend.alignment:Qt.AlignLeft
            antialiasing: true

            DateTimeAxis {
                id:x_axis_other
                format: "hh:mm:ss"
                tickCount: 10
                visible: false
            }

            ValueAxis{
                id: valueLiquidFlowAxisY
                min: 0.1
                max: 2
                titleText: "流量 l/min"
            }

            ValueAxis{
                id: valueRotateSpeedAxisY
                min: 0
                max: 600
                titleText: "转速 r/min"
            }

            SplineSeries {
                id: liquidFlowSeries
                axisX: x_axis_other
                axisY: valueLiquidFlowAxisY
                name:"液体流量"
            }



            SplineSeries {
                id: rotateSpeedSeries
                axisX: x_axis_other
                axisYRight:  valueRotateSpeedAxisY
                name:"搅拌转速"
            }
        }
    }



    function toMsecsSinceEpoch(date){
        var msecs=date.getTime();
        return msecs;
    }
    function timeScope(){
        //间隔改为设定时长
        var nowTime=new Date()
        x_axis.max=nowTime
        x_axis_air.max=nowTime
        x_axis_other.max=nowTime
        x_axis.min=new Date(nowTime.setSeconds(nowTime.getSeconds()-realTimeCurveBackend.x_count))
        x_axis_air.min=new Date(nowTime.setSeconds(nowTime.getSeconds()-realTimeCurveBackend.x_count))
        x_axis_other.min=new Date(nowTime.setSeconds(nowTime.getSeconds()-realTimeCurveBackend.x_count))
    }

    Connections{
        target: realTimeCurveBackend
        function onSignalValChanged(signalVals){
            //创建时间数组，长度根据指定时长除以采集周期,去头加尾
            //数量=实时显示时长/采集周期;
            //通过个数属性传递

            var curd=toMsecsSinceEpoch(new Date())
            timeScope()
            if(locate>=realTimeCurveBackend.x_count){
                if(locate>realTimeCurveBackend.count){
                    airFlowSeries.slice(-realTimeCurveBackend.x_count,-1)
                    airPressSeries.slice(-realTimeCurveBackend.x_count,-1)
                    liquidFlowSeries.slice(-realTimeCurveBackend.x_count,-1)
                    rotateSpeedSeries.slice(-realTimeCurveBackend.x_count,-1)
                    tempSeries.slice(-realTimeCurveBackend.x_count,-1)
                    temp2Series.slice(-realTimeCurveBackend.x_count,-1)
                    temp3Series.slice(-realTimeCurveBackend.x_count,-1)
                    temp4Series.slice(-realTimeCurveBackend.x_count,-1)
                    temp5Series.slice(-realTimeCurveBackend.x_count,-1)
                    locate=realTimeCurveBackend.x_count
                }
                airFlowSeries.remove(0)
                airPressSeries.remove(0)
                liquidFlowSeries.remove(0)
                rotateSpeedSeries.remove(0)
                tempSeries.remove(0)
                temp2Series.remove(0)
                temp3Series.remove(0)
                temp4Series.remove(0)
                temp5Series.remove(0)
                airFlowSeries.append(curd,signalVals[0] )
                airPressSeries.append(curd,signalVals[1] )
                rotateSpeedSeries.append(curd,signalVals[2] )
                liquidFlowSeries.append(curd,signalVals[3] )

                //                console.log(signalVals[3])
                tempSeries.append(curd,signalVals[4] )
                temp2Series.append(curd,signalVals[5] )
                temp3Series.append(curd,signalVals[6] )
                temp4Series.append(curd,signalVals[7] )
                temp5Series.append(curd,signalVals[8] )
            }else{

                airFlowSeries.append(curd,signalVals[0])
                airPressSeries.append(curd,signalVals[1])
                rotateSpeedSeries.append(curd,signalVals[2])
                liquidFlowSeries.append(curd,signalVals[3])

                tempSeries.append(curd,signalVals[4] )
                temp2Series.append(curd,signalVals[5] )
                temp3Series.append(curd,signalVals[6] )
                temp4Series.append(curd,signalVals[7] )
                temp5Series.append(curd,signalVals[8] )

                locate=locate+1;
            }

        }
    }
}
