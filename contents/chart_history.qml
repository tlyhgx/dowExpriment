import QtQuick 2.0
import QtCharts 2.15
import QtQuick.Controls 2.15
Item {
    id:top_level
    width:1680;height: 800
    ChartView{
        id:charView
        width: top_level.width
        height: top_level.height-100
        title: "历史曲线"

        //是否反锯齿化
        antialiasing: true

        Component.onCompleted: {

        }

        ValueAxis{
            id: valueTemAxisY
            min: 0
            max: 200

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

        }

    }


    //添加操作人员实验名称、模拟量通道 combobox
    Row{
        anchors.horizontalCenter: parent.horizontalCenter
        y:charView.height+20
        spacing: 20
        Row{

            spacing: 5
            Label{
                text: "实验人员"
                font.pixelSize: 18
                anchors.verticalCenter:  parent.verticalCenter
            }
            ComboBox{
                //实验人员
                model: ListModel{
                    ListElement{text:"Banana"}
                    ListElement{text:"apple"}
                    ListElement{text:"Banana"}
                }
            }
        }

        Row{
            spacing: 5
            Label{
                text: "实验名称"
                font.pixelSize: 18
                anchors.verticalCenter:  parent.verticalCenter
            }
            ComboBox{
                //实验名称
                model: ListModel{
                    ListElement{text:"Banana"}
                    ListElement{text:"apple"}
                    ListElement{text:"Banana"}
                }
            }
        }

        //选择要显示的模拟量
        Row{
            spacing: 5
            Label{
                text: "数值项"
                font.pixelSize: 18
                anchors.verticalCenter:  parent.verticalCenter
            }
            ComboBox{

                model: ListModel{
                    ListElement{text:"Banana"}
                    ListElement{text:"apple"}
                    ListElement{text:"Banana"}
                }
            }
        }

        HwwButton{
            text: "确定"
        }


    }



    //时间范围combobox   分钟、小时 ，如果滚轮可用另外考虑




}
