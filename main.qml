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



    Image {
            anchors.fill: parent
            source: "images/hero.png"
    }

    Rectangle {
           width: 100
           height: 100
           color: "red"
           anchors.horizontalCenter: parent.horizontalCenter
               anchors.top: parent.top
               anchors.topMargin: 50
       }

       // Зеленый квадрат
       Rectangle {
           width: 100
           height: 100
           color: "green"
           anchors.horizontalCenter: parent.horizontalCenter
               anchors.bottom: parent.bottom
               anchors.bottomMargin: 50
       }


       SoundEffect {
           id: shootSound
           source: "qrc:/sounds/shoot.wav"
           volume: 1.0
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

        Button {
            text: "+1"
            onClicked: {
                shootSound.play()
                score++
                settings.savedScore = score
            }
        }

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
