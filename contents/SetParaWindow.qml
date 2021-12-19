import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
Window {
    title: qsTr("参数设置")
    height: 450
    width: 750

    Grid{


        width: parent.width
        height: parent.height-20
        columns:2
        padding: 50

        rowSpacing: 30
        columnSpacing: 40

        spacing: 5
        flow:Grid.LeftToRight
        ParaItem{
            width: 300
            height: 20
            id:recordCycle
            paraName: "数据记录周期:"
            currentVal_dis: setParaBackend.recordRecycle_s
            unit_dis: "s"

        }
        ParaItem{
            width: 300
            height: 20
            id:curveFlashCycle
            paraName: "曲线刷新周期:"
            currentVal_dis: setParaBackend.realTimeCurve_flashcycle_s
            unit_dis: "s"
        }
        ParaItem{
            width: 300
            height: 20
            id:curveDisDuration
            paraName: "曲线显示时长:"
            currentVal_dis: setParaBackend.realTimeCurve_time_s
            unit_dis: "s"
        }


        ParaItem{
            width: 300
            height: 20
            id:askPLCCycle
            paraName: "数据读取周期:"
            currentVal_dis: setParaBackend.askPlc_cycle_ms
            unit_dis: "ms"
        }

        ParaItem{
            width: 300
            height: 20
            id:tem1HighAlarmVal
            paraName: "温度1高位值"
            currentVal_dis: 0
            unit_dis: "℃"
        }

        ParaItem{
            width: 300
            height: 20
            id:tem2HighAlarmVal
            paraName: "温度2高位值"

            unit_dis: "℃"
        }

        ParaItem{
            width: 300
            height: 20
            id:tem1IncreaseAlarmVal
            paraName: "温度1上升速率值"

            unit_dis: "S/℃"
        }

        ParaItem{
            width: 300
            height: 20
            id:temFallBackVal
            paraName: "温度回差值"
            unit_dis: "℃"
        }

        ParaItem{
            width: 300
            height: 20
            id:airFlowLowVal
            paraName: "气体流量低位值"
            unit_dis: "SLPM"
        }

        ParaItem{
            width: 300
            height: 20
            id:liquidFlowLowVal
            paraName: "液体流量低位值"
            unit_dis: "l/min"
        }
        ParaItem{
            width: 300
            height: 20
            id:rotateLowVal
            paraName: "最低转速"
            unit_dis: "r/min"
        }

        ParaItem{
            width: 300
            height: 20
            id:airPressHighVal
            paraName: "气压最大值"
            unit_dis: "kpa"
        }
        //显示 到plc的参数 --温度1高位报警值(℃）  --温度2高位报警值（℃）  --温度1上升速率报警值(s/℃)  --温度回差值（℃）  --气体流量最小值（SLPM)  --液体流量最小值(L/min)  --转速最小值(r/min)  --相对气压最大值(kpa)  并设置到PLC

    }


    Connections{
        target: setParaBackend
        function onSendParaFromPlcToView(paras){
            tem1HighAlarmVal.nowVal=paras[0]
            tem2HighAlarmVal.nowVal=paras[1]
            tem1IncreaseAlarmVal.nowVal=paras[2]
            airFlowLowVal.nowVal=paras[3]
            liquidFlowLowVal.nowVal=paras[4]
            rotateLowVal.nowVal=paras[5]
            airPressHighVal.nowVal=paras[6]
            temFallBackVal.nowVal=paras[7]
        }
    }
    Label{
        x:10
        y:parent.height-35
        width: 300
        height: 30
        text: "格式：参数名称--当前值--输入框（输入需要改变的给定值，不改无需填写）"
        font.pixelSize: 16
        font.bold: true
    }
    Row{
        x:parent.width-220
        y:parent.height-50
        //        width: 200
        spacing: 5
        HwwButton{

            width: 70
            text: "读取"
            onClicked: {
                var paras=setParaBackend.readPara()
                //TODO:考虑把数据库读取的也更新一下
            }
        }
        HwwButton{
            width: 70
            text: "保存"
            anchors.margins: 5
            onClicked: {

                var recordCycle_s=parseFloat(recordCycle.inputVal)

                if(recordCycle_s&&(recordCycle_s>1)&&(recordCycle_s<100)){
                    setParaBackend.recordRecycle_s=recordCycle_s
                }
                var realTimeCurve_flashcycle_s=parseFloat(curveFlashCycle.inputVal)
                if(realTimeCurve_flashcycle_s&&(realTimeCurve_flashcycle_s>=1))
                {   setParaBackend.realTimeCurve_flashcycle_s=realTimeCurve_flashcycle_s
                }
                var realTimeCurve_time_s=parseFloat(curveDisDuration.inputVal)
                if(realTimeCurve_time_s&&(realTimeCurve_time_s>=60))
                { setParaBackend.realTimeCurve_time_s=realTimeCurve_time_s}

                var askPlc_cycle_ms=parseFloat(askPLCCycle.inputVal)
                if(askPlc_cycle_ms&&(askPlc_cycle_ms>=300)&&(askPlc_cycle_ms<=5000))
                {setParaBackend.askPlc_cycle_ms=askPlc_cycle_ms}

                var valSetToPlcs=new Array;
                var tem1HighAlarmInputVal=parseFloat(tem1HighAlarmVal.inputVal)
                var tem2HighAlarmInputVal=parseFloat(tem2HighAlarmVal.inputVal)
                var tem1IncreaseAlarmInputVal=parseFloat(tem1IncreaseAlarmVal.inputVal)
                var airFlowLowInputVal=parseFloat(airFlowLowVal.inputVal)
                var liquidFlowLowInputVal=parseFloat(liquidFlowLowVal.inputVal)
                var rotateLowInputVal=parseFloat(rotateLowVal.inputVal)
                var airPressHighInputVal=parseFloat(airPressHighVal.inputVal)
                var temFallBackInputVal=parseFloat(temFallBackVal.inputVal)



                if(tem1HighAlarmInputVal&&tem1HighAlarmInputVal<=400)
                {valSetToPlcs.push(tem1HighAlarmInputVal)}else{valSetToPlcs.push(tem1HighAlarmVal.nowVal)}
                if(tem2HighAlarmInputVal&&tem2HighAlarmInputVal<=400)
                {valSetToPlcs.push(tem2HighAlarmInputVal)}else{valSetToPlcs.push(tem2HighAlarmVal.nowVal)}
                if(tem1IncreaseAlarmInputVal&&tem1IncreaseAlarmInputVal<=10)
                {valSetToPlcs.push(tem1IncreaseAlarmInputVal)}else{valSetToPlcs.push(tem1IncreaseAlarmVal.nowVal)}
                if(airFlowLowInputVal&&airFlowLowInputVal>=0)
                {valSetToPlcs.push(airFlowLowInputVal)}else{valSetToPlcs.push(airFlowLowVal.nowVal)}
                if(liquidFlowLowInputVal&&liquidFlowLowInputVal>=0)
                {valSetToPlcs.push(liquidFlowLowInputVal)}else{valSetToPlcs.push(liquidFlowLowVal.nowVal)}
                if(rotateLowInputVal&&rotateLowInputVal>=0)
                {valSetToPlcs.push(rotateLowInputVal)}else{valSetToPlcs.push(rotateLowVal.nowVal)}
                if(airPressHighInputVal&&airPressHighInputVal>=0)
                {valSetToPlcs.push(airPressHighInputVal)}else{valSetToPlcs.push(airPressHighVal.nowVal)}
                if(temFallBackInputVal&&temFallBackInputVal>=1&&temFallBackInputVal<=20)
                {valSetToPlcs.push(temFallBackInputVal)}else{valSetToPlcs.push(temFallBackVal.nowVal)}

                setParaBackend.setPlcPara(valSetToPlcs);
            }
        }
        HwwButton{
            width: 70
            text: "退出"
            anchors.margins: 5
            onClicked: {
                setParaWindow.close()
            }

        }
    }

}
