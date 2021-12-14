import QtQuick 2.0

ListView {
    width: 200
    height: 120

    required infoModel

    delegate:Text{
        required property string infoTime;
        required property string info;

        text: infoTime+":"+info
    }

}
