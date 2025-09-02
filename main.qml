import QtQuick
import QtQuick.Controls
import Qt.labs.settings 1.0
import QtMultimedia

ApplicationWindow {
    visible: true
    width: 400
    height: 600
    title: "Mini Game"


    Settings {
        id: settings
        property int savedScore: 0
    }

    property int score: settings.savedScore

    Text {
        text: "Выстрел (осталось " + hero.ammo + ")"
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 20  // отступ от краёв
        font.pixelSize: 20   // размер текста
        color: "black"       // цвет текста
    }

   /* Image {
            anchors.fill: parent
            source: "images/hero.png"
    }*/

    Rectangle {
           width: 100
           height: 100
           color: "red"
           anchors.horizontalCenter: parent.horizontalCenter
               anchors.top: parent.top
               anchors.topMargin: 50
       }



        Rectangle {
            width: 100
            height: 100
            color: hero.color
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
        }

        Button {

            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            height: parent.height / 2

            background: Rectangle {
               color: "transparent"
            }
            onClicked: {

                hero.shooting()
                score++
                settings.savedScore = score
        }

    }
    Column {
        anchors.centerIn: parent
        spacing: 20

        Label {
            text: "Score: " + score
            font.pixelSize: 32
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
        }

       /* Button {
            text: "+1"
            onClicked: {
                shootSound.play()

            }
        }*/

        Button {
            text: "Reset"
            onClicked: {
                score = 0
                settings.savedScore = score
            }
        }


        Label {
            text: "Timer: " + timerLogic.seconds
            font.pixelSize: 28
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
        }
    }
}
