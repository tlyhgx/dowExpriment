import QtQuick 2.0
import "../learn"

Item {
    width: 800;height: 800
//    AnimationEx1{}
    Ball1{
    id:ball}
    MouseArea{
        anchors.fill: parent
        onClicked: {
            ball.color=Qt.tint(ball.color,"#10FF0000")
            ball.x+=100
            ball.y+=100
        }
    }
}
