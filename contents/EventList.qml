import QtQuick 2.0

Item {
    width: 200;
    height: 150;

    ListModel {
        id:infoList
        ListElement {
            time: "new Date()";
            event: "开始记录";
        }
        ListElement {
            time: "new Date()";
            event: "温度过高";
        }

    }
    ListView{

        anchors{fill:parent;margins: 2}
        model: infoList
        delegate: dragDelegate

        spacing: 4
        cacheBuffer: 50

    }
    Component {
        id: dragDelegate

        Rectangle {
            id: content

            anchors { left: parent.left; right: parent.right }
            height: column.implicitHeight + 4

            border.width: 1
            border.color: "lightsteelblue"

            radius: 2

            Row {
                id: column
                anchors { fill: parent; margins: 2 }

                Text { text: '时间: ' + time }
                Text { text: '事件: ' + event }

            }
        }
    }
}
