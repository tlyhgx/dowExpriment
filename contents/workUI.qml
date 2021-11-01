import QtQuick 2.0

Item {
    id:workUI;
    width: 720;
    height: 460;


    Image {
        id: tank
        source: "../imgs/tank.png"
        width: 200;
        height:300;
        x:350;
        y:80;
    }

    Image {
        id: mix
        source: "../imgs/mixer.png"
        width: 80;
        height:300;
        x:tank.x+tank.width/2-width/3;
        y:tank.y-100;
    }


}
