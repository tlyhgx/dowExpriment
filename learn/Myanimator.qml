import QtQuick 2.9
import QtQuick.Window 2.3

Window {
    visible: true
    width: 640
    height: 480

    Rectangle {
        id: mixBox
        width: 50
        height: 50
        ParallelAnimation {
            ColorAnimation {
                target: mixBox
                property: "color"
                from: "forestgreen"
                to: "lightsteelblue";
                duration: 3000
                loops:Animation.Infinite
            }
            ScaleAnimator {
                target: mixBox
                from: 2
                to: 1
                loops:Animation.Infinite
                duration: 3000
            }
            running: true
        }
    }
}
