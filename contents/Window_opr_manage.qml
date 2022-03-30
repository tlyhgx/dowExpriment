import QtQuick 2.0
import backend_oper_manage 1.0
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
Window {
    id:id_top_level
    width: 660;height: 400
    flags: Qt.FramelessWindowHint
    Backend_oper_manage{
        id:backend_oper_manage
    }
    Rectangle{
        x:100
        y:50
        border.width: 1
        radius: 4
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

//                    anchors.horizontalCenter: parent.horizontalCenter
                }


                HwwButton{
                    text: "添加"
                    anchors.right:  parent.right
                    MouseArea{
                    onClicked: backend_oper_manage.addOper(selItem_addItem.text)
                    }
                }
                HwwButton{
                    text: "删除"
                    anchors.right:  parent.right
                }
                HwwButton{
                    text: "修改"
                    anchors.right:  parent.right
                }
            }


        }


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

