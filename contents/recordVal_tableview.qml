import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import recordValTableModel 1.0

Item {
    id:root
    property string tableName: "signal_vals"
    property int verHeaderHeight: 30
    property int verHeaderWidth: 30
    property int horHeaderHeight: 30
    property var columnWidthArr: [200,100,100]   //定义列宽数值
    property var experiment_name: []


    RecordValTableModel{id:table_model;m_tableName:tableName

    }
//    ColumnLayout{
//        id:selectItem
//        x:parent.width-200
//        y:20
//        height: 200
//        width: 120


//        HwwButton{
//            text: "查询"
//        }
//    }


    ComboBox{
            editable: false
            x: 10
            y:10

            Component.objectName:
            {
                var items=table_model.search_expriment_name()

                for(var i in items)
                {
                    experiment_name.push(items[i])
                }
//                console.log(experiment_name)
//                console.log(table_model.search_expriment_name())
            }
            model: experiment_name

    }


    TableView{
        id:tableView

        x: 10
        y:40
        columnSpacing: 1
        columnWidthProvider: function(column){
            return root.columnWidthArr[column]
        }
        rowHeightProvider: function(row){
            return root.verHeaderHeight;
        }

        Layout.margins: 15
        anchors{
            fill:parent
            leftMargin: root.verHeaderWidth
            topMargin: root.horHeaderHeight
        }

        model: table_model
        clip: true
        delegate: Rectangle{
            width: tableView.columnWidthProvider(table_model.row)
            height: horHeaderHeight
            Label{
                id:label
                text:model.name
                anchors.fill: parent
                anchors.margins: 10
                color: "black"
                font.pixelSize: 15
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }


        }
    }

    //定义横向表头
    Item{
        id:header_horizontal
        anchors{
            left: parent.left
            right: parent.right
            leftMargin: root.verHeaderWidth

        }
        height: root.horHeaderHeight
        z:2
        Row{
            id:header_horizontal_row
            anchors.fill: parent
            leftPadding: -tableView.contentX
            clip: true
            spacing: 0

            Repeater{
                model: tableView.columns>0?tableView.columns:0

                Rectangle{
                    id: header_horizontal_item
                    width: tableView.columnWidthProvider(index)+tableView.columnSpacing
                    height: root.horHeaderHeight
                    color: "#1C77C3"

                    Text{
                        anchors.centerIn: parent
                        text: table_model.headerData(index,Qt.Horizontal)
                        color: "white"
                    }

                    Rectangle{
                        width: 1
                        height: parent.height
                        anchors.right: parent.right
                        color: "black"
                        opacity: 0.5
                    }
                }
            }
        }

    }
    //定义纵向表头
    Column{
        id:header_verical
        anchors{
            top:parent.top
            bottom: parent.bottom
            topMargin: root.horHeaderHeight
        }

        topPadding: -tableView.contentY
        z:2
        clip: true
        spacing: 1
        Repeater{
            model: tableView.rows>0?tableView.rows:0  //返回模型的行数
            Rectangle{
                width: root.verHeaderWidth
                height: tableView.rowHeightProvider(index)
                color: "#1C77C3"
                Text{
                    anchors.centerIn: parent
                    text:table_model.headerData(index,Qt.Vertical)
                    color:"white"
                }
            }

        }

    }

    onTableNameChanged: {
        //        console.log("tableName changed")
        tableView.forceLayout()
    }
}
