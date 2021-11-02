import QtQuick 2.0
import QtQuick.Controls 1.4

Item {
    TableView{
        id:tableView;
        frameVisible: true;
//        anchors.fill: parent;
        width:360
        height:300

        model: ListModel{
            id:listModel
            ListElement{
                time:"2021-11-01 10:23:19"
                content:"开始实验";

            }
            ListElement{
                time:"2021-11-01 11:23:19"
                content:"1#温度检测过高！";

            }
            ListElement{
                time:"2021-11-01 12:23:19"
                content:"气体流量过小！";
            }
        }

        Component{
            id:itemDelegateText
            Text{
            anchors.verticalCenter: parent.verticalCenter;
            color: styleData.selected?"#1E90FF":"#000000";
            elide: styleData.elideMode;
            text: styleData.value;
            font.pointSize: 12;
            font.bold: true;
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
            anchors.fill: parent;
            }
        }

        TableViewColumn{
            role:"time"
            title:qsTr("时间")
            width: 150
            delegate: itemDelegateText
        }
        TableViewColumn{
            role:"content"
            title:qsTr("事件")
            width: 150
            delegate: itemDelegateText
        }

        headerDelegate: Rectangle{
            height: 30
            border.width: 1
            color: "#FAEBD7"
            border.color: "#04f6f6"
            Text {
                id: headerName

                text: styleData.value
                font.pointSize: 15
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.fill:parent
            }
        }

        rowDelegate: Rectangle{
            id:rowRectangle
            property color rowColor: styleData.selected?"#FFDEAD":(styleData.alternate?"#F0FFF0":"#E6E6FA")
            color: rowColor
            height: 30
            Rectangle{
                x:100
                height: parent.height
                width: 1
                color: "black"
            }

        }
    }
}
