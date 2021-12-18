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
        columnSpacing: 20

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

        //TODO1:1显示  实时曲线刷新周期，实时曲线显示时间长度， 读取数据周期（默认500ms,保存时要判断>300 <5000)  并保存到数据库(要判断）
        //TODO1: 显示 到plc的参数 --温度1高位报警值(℃）  --温度2高位报警值（℃）  --温度1上升速率报警值(s/℃)  --温度回差值（℃）  --气体流量最小值（SLPM)  --液体流量最小值(L/min)  --转速最小值(r/min)  --相对气压最大值(kpa)  并设置到PLC






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
        x:parent.width-160
        y:parent.height-50
        //        width: 200
        spacing: 5
        HwwButton{
            width: 70
            text: "保存"
            anchors.margins: 5
            onClicked: {

                var recordCycle_s=parseFloat(recordCycle.inputVal)
                //                console.log(recordCycle_s)
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
                //TODO1:

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
