import QtQuick 2.15

import Qt.labs.qmlmodels 1.0

Item {
    width: 200;
    height: 180;

    TableView {
        anchors.fill: parent
//        frameVisible:false;
        columnSpacing: 1
        rowSpacing: 1
//        clip: true



        model: TableModel {
            TableModelColumn { display: "time" }
            TableModelColumn { display: "event" }

            rows: [
                {
                    "time": "2021-11-01 12:23:32",
                    "event": "启动实验"
                },
                {
                    "time": "2021-11-01 12:32:32",
                    "event": "3#温度过高！"
                },
                {
                    "time": "2021-11-01 13:23:32",
                    "event": "气体流量太小！"
                }
            ]
        }

        delegate: Rectangle {
            implicitWidth: 180
            implicitHeight: 30
            border.width: 1

            Text {
                text: display
                anchors.centerIn: parent
            }
        }
    }


}
