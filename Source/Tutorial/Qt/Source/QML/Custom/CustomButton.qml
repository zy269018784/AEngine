import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15


Rectangle
{
    id: control
    width: 120
    height: 40
    color: "#550000ff"

    Text
    {
        text: "hello world"
        font.pixelSize: 14
        font.bold: true
        color: control.down ? "#e3f2fd" : "#ffffff"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    MouseArea {
        hoverEnabled: true
        anchors.fill: parent
/*
        onContainsMouseChanged: {
            if (containsMouse) {
                console.log("鼠标进入了")
                control.color = "red"
                // 执行进入时的逻辑
            } else {
                console.log("鼠标离开了")
                control.color = "blue"
                // 执行离开时的逻辑
            }
        }
*/

    }
}