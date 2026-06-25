import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

Button {
    id: control
    text: "自定义按钮"
    width: 120
    height: 40
    /*
    * 自定义背景
    * */
    background: Rectangle {
        /*
        * 宽度和高度
        * */
        implicitWidth: 100
        implicitHeight: 40
        /*
        * 圆角
        * */
        radius: 8
        /*
        *   down和hovered状态下的背景颜色
        * */
        color: control.down ? "#1e88e5" : (control.hovered ? "#42a5f5" : "#2196f3")

        border.width: 2
        /*
        *   down和hovered状态下的边框颜色
        * */
        border.color: "#FF0000"

    }

    // 自定义文字
    contentItem: Text
    {
        text: control.text
        font.pixelSize: 14
        font.bold: true
        color: control.down ? "#e3f2fd" : "#ffffff"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    ToolTip {
        text: "这是一个用于提交表单的按钮"
        visible: parent.hovered
        delay: 200
        timeout: 5000
        position: ToolTip.Right
    }
}