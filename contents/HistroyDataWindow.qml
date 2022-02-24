import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
Window {
    title: qsTr("历史记录")
    height: 1000
    width: 750
    flags: Qt.FramelessWindowHint




    Rectangle{
        anchors.fill: parent
        anchors.margins: 10
        color: "lightblue"
        RecordVal_tableview{
            id:recordVal_tableview
            height: parent.height
            width: 500



        }




    }
    HwwButton{
        x:parent.width-100
        y:parent.height-80
        z:1
        text: "退出"
        onClicked: {
            historyDataWindow.hide()
        }
    }
}
