import QtQuick 2.0
import backend_oper_manage 1.0
Item {
    id:id_top_level
    width: 660;height: 400

    ListView{
        x:100
        y:50
        width: 200
        height: id_top_level.height-100
        model: Backend_oper_manage{}
        delegate:Text {
            text: "cs"
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
//            window_adjust_value.hide()
        }

    }
}
