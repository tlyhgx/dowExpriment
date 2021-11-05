import QtQuick 2.0

Item {
    width: 400;height: 500
    Rectangle{
        color: "lightblue"
        width: 100;height:100
        Rectangle{
            color: "blue"
            width: 25;height: 25
        }
        Rectangle{
            color: "yellow"
            x:25;y:25;width:25;height: 25
            scale: 1.6
        }
        Rectangle{
            color: "lightgrey"
            x:25;y:25;width:50;height: 50
            rotation: 30
            scale: 1.6
        }
    }
    Row{
        x:200;y:200
        spacing:10

        Image {
            id: name
            source: "../imgs/mixer.png"

        }
        Image {
            id: name1
            source: "../imgs/mixer.png"
            transform: Rotation{origin.x:30;origin.y:30;
            axis{x:0;y:1;z:0}angle:45 }
        }
    }


}
