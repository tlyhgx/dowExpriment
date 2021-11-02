import QtQuick 2.0
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0


    Button {
        id: ssqx
        property color backgroundDefaultColor: "#4E5BF2"
        property color backgroundPressedColor: Qt.darker(backgroundDefaultColor, 1.2)
        property color contentItemTextColor: "white"


        text: thisText
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

