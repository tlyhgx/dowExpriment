import QtQuick 2.0
import backend_oper_manage 1.0
import QtQuick.Window 2.15
Window {
    id:id_top_level
    width: 660;height: 400
    Backend_oper_manage{
        id:backend_oper_manage
    }

    //名字列表
    ListView{
        id:list_name
        x:100
        y:50
        width: 200
        height: id_top_level.height-100
        focus: true
        highlight: Rectangle{color:"lightsteelblue";radius:5}
        highlightFollowsCurrentItem: true
        model: backend_oper_manage.list_operName
        delegate: names_delegate
        header: Component{Text {
                id: name
                text: qsTr("实验人员姓名")
            }
        }
    }


    //名字列表显示样式
    Component{
        id:names_delegate
        Rectangle{
            width: 60;height: 30
            //            border.color: "lightblue"
            Text {

                //                text:data[index]
                text:'<b> '+backend_oper_manage.list_operName[index]+' </b>'
            }
        }
    }


    Column{
        x:id_top_level.width-100
        y:50
        spacing: 30

        HwwButton{
            text: "添加"
        }
        HwwButton{
            text: "删除"
        }
        HwwButton{
            text: "修改"
        }
    }


    HwwButton{
        x:id_top_level.width-100
        y:id_top_level.height-50
        text: "退 出"
        onClicked: {
            window_opr_manage.close()
        }

    }
}

