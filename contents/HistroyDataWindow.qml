import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Window {
    title: qsTr("历史记录")
    height: 1000
    width: 1680
    flags: Qt.FramelessWindowHint
    //TODO:窗口居中要设置








    Chart_history{
        id:chart_history
        height: parent.height-50
        width: parent.width
        anchors.margins: 10

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
