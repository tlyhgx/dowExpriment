import QtQuick 2.12
import QtQuick.Window 2.12
Window {
    title: qsTr("历史记录")
    height: 450
    width: 750
    flags: Qt.FramelessWindowHint
    Rectangle{

        anchors.fill: parent
        color: "lightblue"
        HwwButton{
            x:parent.width-100
            y:20
            z:1
            text: "退出"
            onClicked: {
                historyDataWindow.hide()
            }
        }
    }
}
