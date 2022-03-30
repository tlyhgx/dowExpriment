import QtQuick 2.0
import backend_oper_manage 1.0
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
Window {
    id:id_top_level
    width: 660;height: 400
    flags: Qt.FramelessWindowHint
    Backend_oper_manage{
        id:backend_oper_manage
    }
    Frame{
        x:100
        y:50

        width: 360
        height:id_top_level.height-100
        Row{
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            spacing: 20
            //名字列表
            Column{
                spacing: 10

                //头部名称
                Rectangle{
                    width: list_name.width;height: 35
                    gradient: clubcolors
                    border {color: "#9EDDF2"; width: 2}
                    Text {
                        text: "实验人员名称"
                        color: "darkblue"
                        font.pixelSize: 20
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    radius: 4
                }


                //列表内容
                ListView{
                    id:list_name
                    clip: true
                    width: 140
                    height: id_top_level.height-180

                    highlight: Rectangle{
                        color:"azure"
                        radius:5
                        width: list_name.width
                    }
                    highlightFollowsCurrentItem: true
                    model: backend_oper_manage.list_operName
                    delegate: Component{

                        Item{
                            height: 24;width: parent.width

                            Text {
                                text: model.modelData
                                font.pixelSize: 20

                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked: {
                                    list_name.currentIndex=index
                                }
                            }
                        }
                    }

                    onCurrentIndexChanged: {
                        selItem_addItem.text=backend_oper_manage.list_operName[currentIndex]
                    }


                    Gradient {
                        id: clubcolors
                        GradientStop { position: 0.0; color: "#8EE2FE"}
                        GradientStop { position: 0.66; color: "#7ED2EE"}
                    }






                }
            }
            //curd按钮组
            Column{

                spacing: 20

                //待修改和输入框
                Rectangle{
                    x:10;y:10
                    width: 120;height: 30
                    radius: 4
                    border.width: 1

                    TextInput{
                        id:selItem_addItem
                        anchors.fill: parent
                        font.pointSize: 12
                        selectByMouse: true
                        focus: true
                        verticalAlignment: Qt.AlignVCenter
                        horizontalAlignment: Qt.AlignHCenter
                    }
                }


                HwwButton{
                    text: "添加"
                    anchors.right:  parent.right

                        onClicked:
                        {
                            backend_oper_manage.add_oper(selItem_addItem.text)
//                            console.log("添加用户")
                        }

                }
                HwwButton{
                    text: "删除"
                    anchors.right:  parent.right
                    onClicked: {
                        dlg_del_oper_confirm.open()


                    }
                }
                HwwButton{
                    text: "修改"
                    anchors.right:  parent.right
                    onClicked: {
                    backend_oper_manage.update_oper(selItem_addItem.text,backend_oper_manage.list_operName[list_name.currentIndex])
                    }
                }
            }
        }


    }

    //询问是否删除用户对话框
    Dialog {
        id: dlg_del_oper_confirm
        title: "确定删除此用户！"
        standardButtons: Dialog.Ok | Dialog.Cancel

        onAccepted: {
            //提示窗口“确定删除！”
            backend_oper_manage.del_oper(selItem_addItem.text)
        }
        onRejected: dlg_del_oper_confirm.close()
    }

    //退出按钮
    HwwButton{
        x:id_top_level.width-100
        y:id_top_level.height-50
        text: "退 出"
        onClicked: {
            window_opr_manage.close()
        }
    }
}

