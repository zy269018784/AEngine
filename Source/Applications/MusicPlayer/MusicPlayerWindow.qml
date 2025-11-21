import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts
import QtQuick.Controls

Window {
    id: window
    width: 400
    height: 300
    visible: true
    title: qsTr("Hello QML")
    Rectangle {
        x: 0
        y: 0
        width: parent.width
        height: parent.height - 50
        color: "red"
    }
    Rectangle {
        x: 0
        y: parent.height - 50
        width: parent.width
        height: 50
        MyButton1 {
            x: 0
            text: "Prev"
            width: 50
            height: 50
        }
        MyButton1 {
            x: 50
            text: "Play"
            width: 50
            height: 50
        }
        MyButton1 {
            x: 100
            text: "Next"
            width: 50
            height: 50
        }

        Label {
            x: 150
            width: 100
            height: parent.height
            text: "5:30"
            verticalAlignment: Text.AlignVCenter
        }
        Label {
            x: 350
            width: 100
            height: parent.height
            text: "5:30"
            verticalAlignment: Text.AlignVCenter
        }
    }

}