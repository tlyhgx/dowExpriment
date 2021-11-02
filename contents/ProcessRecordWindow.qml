import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
Window {
    id:processRecWin
    title: qsTr("过程记录")
    height: 450
    width: 750
    Rectangle{

        anchors.fill: parent
        color: "lightblue"
    }
    Button{
        height: 30
        width: 50
        x:120
        y:40
        text: "退出"
        MouseArea{
            anchors.fill: parent
            onClicked: {
                processRecWin.close()
            }
        }
    }
}
