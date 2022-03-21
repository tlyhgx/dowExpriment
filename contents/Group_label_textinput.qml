import QtQuick 2.0
import QtQuick.Controls 2.0

Item {
    property string paraName: "label_info"
    property alias setVal: inputVal.text
    Row{
        spacing: 6
        Label {
            text: paraName
            font.pixelSize: 18
            font.bold: true
            anchors.verticalCenter: parent.verticalCenter
        }
        TextField {
            width:70
            height: 28
            anchors.leftMargin: 10
            id:inputVal;
            font{
                pixelSize: 18
                bold: true
            }
            selectByMouse: true
            horizontalAlignment: "AlignRight"
            verticalAlignment: "AlignBottom"
                    validator: RegExpValidator{regExp:/^(\-)?\d+(\.\d{1,2})$/}
        }
    }
}
