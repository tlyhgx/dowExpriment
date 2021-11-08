import QtQuick 2.15
import QtQuick.Controls 2.12

Item {
    width: 100;height: 60
    property string deviceName: "元器件"
    property var value: 0.00
    property string unit: "℃"



    Column{
        anchors.centerIn: parent
        spacing: 2
        Row{
            width: 90;height:30

            Rectangle{
                width: 70;height:28
                id:row1
                color: "#1c2239"
                radius: 3

                Label{
                    id:val
                    text:value
                    anchors.fill: parent



                    color: "#e10400"
                    font{
                        pixelSize: 26
                        bold: true}
                    anchors.verticalCenter: parent.verticalCenter
                    horizontalAlignment: Text.AlignRight
                }

            }
            Label{
                width: 20;height:30
                id:unit_id
                text:unit
                color: "#166300"
                font{
                    pixelSize: 24
                    bold: true}
            }
        }

        Rectangle{
            width: 90;height: 25
            color: Qt.rgba(0,0,0,0)
            anchors.horizontalCenter: parent.horizontalCenter

            Label{
                anchors.horizontalCenter: parent.horizontalCenter

                id:name
                text:  deviceName
                color: "darkblue"
                font{
                    pixelSize: 20
                    bold: true}

            }
        }


    }

}

