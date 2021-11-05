import QtQuick 2.12
import EasyModel 1.0
import QtQuick.Controls 2.12
Item {
    id:control
    implicitHeight: 300
    implicitWidth: 500

    //行表头--竖向的
    property int  verHeaderHeight: 30
    property int  verHeaderWidth: 30

    //列表头--横向的
    property int  horHeaderHeight: 30

    //滚动条
    property color  scrollBarColor: "cyan"
    property int  scrollBarWidth: 6

    //列宽
    property variant columnWidthArr: [180,200]


    EasyTableModel{
        id:table_model
        horHeader: ["时间","事件"]
        initData: [
            {"current_time":"2021-11-01 08:32:31","content":"开始实验......"},
            {"current_time":"2021-11-01 08:32:31","content":"1#温度过高"},
            {"current_time":"2021-11-01 08:32:31","content":"气流过低"},
            {"current_time":"2021-11-01 08:32:31","content":"实验结束！"},


        ]

    }

    //表格内容，不含表头
    TableView{
        id:table_view
        anchors{
            fill:parent
            leftMargin: control.verHeaderHeight
            topMargin: control.horHeaderHeight
        }

        clip: true
        boundsBehavior: Flickable.StopAtBounds
        columnSpacing: 1
        rowSpacing: 1
        //此属性可以包含一个函数，该函数返回模型中每行的行高
        rowHeightProvider: function(row){
            return control.verHeaderHeight;
        }

        //此属性可以包含一个函数，该函数返回模型中每列的列宽
        columnWidthProvider: function(column )
        {
            return control.columnWidthArr[column];
        }

        ScrollBar.vertical:ScrollBar{
            id:scroll_vertical
            anchors.right: parent.right
            anchors.rightMargin: 2

            contentItem: Rectangle{
                visible: (scrollBarColor.size<1.0)
                implicitWidth: control.scrollBarWidth
                color: control.scrollBarColor
            }
        }

        ScrollBar.horizontal:ScrollBar {
            id:scroll_horizontal
            anchors.bottom: parent.bottom
            anchors.bottomMargin:2
            contentItem: Rectangle{
                visible: (scroll_horizontal.size<0)
                implicitHeight: control.scrollBarWidth
                color: control.scrollBarColor
            }
        }

        //model是在c++中定义的，和Qt c++是类似的
        model: table_model
        delegate: Rectangle{
            color: (model.row%2)?"lightsteelblue":Qt.darker("lightsteelblue")
            TextInput{
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                selectByMouse: true;
                selectedTextColor:"black"
                selectionColor: "white"

                //获取单元格对应的值
                text: model.value
                onEditingFinished: {
                    model.edit=text;
                    console.log("edit",model.value)
                }
            }
        }
    }

    //横向表头
    Item {
        id: header_horizontal
        anchors{
            left: parent.left
            right: parent.right
            leftMargin: control.verHeaderWidth
        }
        height: control.horHeaderHeight
        z:2
        //暂存鼠标拖动的位置
        property int  posXTemp: 0
        MouseArea{
            anchors.fill: parent
            onPressed: header_horizontal.posXTemp=mouseX
            onPositionChanged: {
                if(table_view.contentX+(header_horizontal.posXTemp-mouseX)>0)
                {
                    table_view.contentX+=(header_horizontal.posXTemp-mouseX);

                }else{
                    table_view.contentX=0;
                }
                header_horizontal.posXTemp=mouseX;
            }
        }
        Row{
            id:header_horizontal_row
            anchors.fill: parent
            leftPadding: -table_view.contentX
            clip: true
            spacing: 0

            Repeater{
                model: table_view.columns>0?table_view.columns:0
                Rectangle{
                    id:header_horizontal_item
                    width: table_view.columnWidthProvider(index)+table_view.columnSpacing
                    height: control.horHeaderHeight
                    color: "lightcyan"

                    Text {
                        anchors.centerIn: parent
                        text: table_model.headerData(index,Qt.Horizontal)
                    }
                    Rectangle{
                        width: 1
                        height: parent.height
                        anchors.right: parent.right
                        color: "black"
                        opacity: 0.5
                    }
                    MouseArea{
                        width: 3
                        height: parent.height
                        anchors.right: parent.right
                        cursorShape: Qt.SplitHCursor
                        onPressed: header_horizontal.posXTemp=mouseX;
                        onPositionChanged: {
                            if((header_horizontal_item.width-(header_horizontal.posXTemp-mouseX))>10){
                                header_horizontal_item.width-=(header_horizontal.posXTemp-mouseX);
                            }else{
                                header_horizontal_item.width=10;
                            }
                            header_horizontal.posXTemp=mouseX;
                            control.columnWidthArr[index]=(header_horizontal_item.width-table_view.columnSpacing);
                            //刷新布局，这样宽度才会改变
                            table_view.forceLayout();
                        }

                    }

                }

            }
        }
    }
    //竖向表头
    Column{
        id:header_verical
        anchors{
            top: parent.top
            bottom: parent.bottom
            topMargin: control.horHeaderHeight
        }
        topPadding: -table_view.contentY
        z:2
        clip: true
        spacing: 1
        Repeater{
            model: table_view.rows>0?table_view.rows:0
            Rectangle{
                width: control.verHeaderWidth
                height: table_view.rowHeightProvider(index)
                color: "#800000FF"
                Text {
                    anchors.centerIn: parent
                    text: table_model.headerData(index+1,Qt.Vertical)
                }
            }
        }
    }
}
