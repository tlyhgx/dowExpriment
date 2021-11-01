import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.15
import QtQuick.Layouts 1.12
import "contents"

Window {
    width: 1204
    height: 768
    visible: true
    title: qsTr("Hello World")
//    Rectangle{
//        width: parent.width;
//        height: parent.height;
//        gradient: Gradient{
//            GradientStop{position:0.0;color:"lightsteelblue"}
//            GradientStop{position:1.0;color:"cyan"}
//        }
//    }

    Alarm{
        z:1;
    }

    WorkUI{

        x:300;
        y:60;
    }
    TextField {
        id: root

        property color checkedColor: "#D5DBDB"

        signal doubleClicked(var/*MouseEvent*/ event)

        placeholderText: qsTr("请输入内容")
        font.family: "Arial"
        font.pixelSize: 15
        font.weight: Font.Thin
        antialiasing: true

        background: Rectangle {
            implicitWidth: 213
            implicitHeight: 42
            radius: 8
            color: root.enabled ? "transparent" : "#F4F6F6"
            border.color: root.enabled ? root.checkedColor : "#D5DBDB"
            border.width: 2
            opacity: root.enabled ? 1 : 0.7

            layer.enabled: root.hovered
            layer.effect: DropShadow {
                id: dropShadow
                transparentBorder: true
                color: root.checkedColor
                samples: 10 /*20*/
            }
        }

        cursorDelegate: Rectangle {
            width: 1
            height: parent.height * 0.4
            color: root.checkedColor
            visible: root.focus

            Timer {
                interval: 600
                repeat: true
                running: root.focus
                onRunningChanged: parent.visible = running
                onTriggered: parent.visible = !parent.visible
            }
        }

        onDoubleClicked: selectAll()

        /* note: This signal was introduced in QtQuick.Controls 2.1 (Qt 5.8). */
        onPressed: {
            _private.mouseEvent = event
            _private.isCheckDoubleClickedEvent++

            if (! _checkDoubleClickedEventTimer.running)
                _checkDoubleClickedEventTimer.restart()
        }

        /* Private */
        Item {
            id: _private
            property int isCheckDoubleClickedEvent: 0
            property var/*MouseEvent*/ mouseEvent

            Timer {
                id: _checkDoubleClickedEventTimer
                running: false
                repeat: false
                interval: 180
                onTriggered: {
                    if (_private.isCheckDoubleClickedEvent >= 2) {
                        /* Double Clicked Event */
                        root.doubleClicked(_private.mouseEvent)
                    }

                    stop()
                    _private.isCheckDoubleClickedEvent = 0
                }
            }
        }
    }
    GridLayout {
        x:300;
        y:300;
        width: 200
        rows: 3
        columns: 3

        Repeater {
            id: textFieldRepeater
            model: ["#727CF5", "#0ACF97", "#F9375E",
                    "#FFBC00", "#2B99B9", "#5A6268",
                    "#EEF2F7", "#212730"]

            TextField {
                placeholderText: "请输入内容："
//                checkedColor: modelData
            }
        }

        TextField {
            enabled: false
            placeholderText: "禁用状态"
        }
    }

    Rectangle{

        width: 300;
        height: 80;
        x:parent.width-450;
        y:parent.height-100;
        Row{
            id: buttonRow
            spacing: 6
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 12
            width: parent.width

            Button {
                id: ssqx
                property color backgroundDefaultColor: "#4E5BF2"
                property color backgroundPressedColor: Qt.darker(backgroundDefaultColor, 1.2)
                property color contentItemTextColor: "white"

                text: "实时曲线"
                contentItem: Text {
                    text: ssqx.text
                    color: ssqx.contentItemTextColor
                    font.pixelSize: 15
                    font.family: "Arial"
                    font.weight: Font.Thin
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }

                background: Rectangle {
                    implicitWidth: 83
                    implicitHeight: 37
                    color: ssqx.down ? ssqx.backgroundPressedColor : ssqx.backgroundDefaultColor
                    radius: 3
                    layer.enabled: true
                    layer.effect: DropShadow {
                        transparentBorder: true
                        color: ssqx.down ? ssqx.backgroundPressedColor : ssqx.backgroundDefaultColor
                        samples: 20
                    }
                }
            }

            Button {
                id: lssj
                property color backgroundDefaultColor: "#4E5BF2"
                property color backgroundPressedColor: Qt.darker(backgroundDefaultColor, 1.2)
                property color contentItemTextColor: "white"

                text: "历史数据"
                contentItem: Text {
                    text: lssj.text
                    color: lssj.contentItemTextColor
                    font.pixelSize: 15
                    font.family: "Arial"
                    font.weight: Font.Thin
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }

                background: Rectangle {
                    implicitWidth: 83
                    implicitHeight: 37
                    color: lssj.down ? lssj.backgroundPressedColor : lssj.backgroundDefaultColor
                    radius: 3
                    layer.enabled: true
                    layer.effect: DropShadow {
                        transparentBorder: true
                        color: lssj.down ? lssj.backgroundPressedColor : lssj.backgroundDefaultColor
                        samples: 20
                    }
                }
            }

            Button {
                id: cssz
                property color backgroundDefaultColor: "#4E5BF2"
                property color backgroundPressedColor: Qt.darker(backgroundDefaultColor, 1.2)
                property color contentItemTextColor: "white"

                text: "参数设置"
                contentItem: Text {
                    text: cssz.text
                    color: cssz.contentItemTextColor
                    font.pixelSize: 15
                    font.family: "Arial"
                    font.weight: Font.Thin
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }

                background: Rectangle {
                    implicitWidth: 83
                    implicitHeight: 37
                    color: cssz.down ? cssz.backgroundPressedColor : cssz.backgroundDefaultColor
                    radius: 3
                    layer.enabled: true
                    layer.effect: DropShadow {
                        transparentBorder: true
                        color: cssz.down ? cssz.backgroundPressedColor : cssz.backgroundDefaultColor
                        samples: 20
                    }
                }
            }

            Button {
                id: bjjl
                property color backgroundDefaultColor: "#4E5BF2"
                property color backgroundPressedColor: Qt.darker(backgroundDefaultColor, 1.2)
                property color contentItemTextColor: "white"

                text: "报警记录"
                contentItem: Text {
                    text: bjjl.text
                    color: bjjl.contentItemTextColor
                    font.pixelSize: 15
                    font.family: "Arial"
                    font.weight: Font.Thin
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }

                background: Rectangle {
                    implicitWidth: 83
                    implicitHeight: 37
                    color: bjjl.down ? bjjl.backgroundPressedColor : bjjl.backgroundDefaultColor
                    radius: 3
                    layer.enabled: true
                    layer.effect: DropShadow {
                        transparentBorder: true
                        color: bjjl.down ? bjjl.backgroundPressedColor : bjjl.backgroundDefaultColor
                        samples: 20
                    }
                }
            }

        }
    }

}
