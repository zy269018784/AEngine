
import QtQuick
import QtQuick.Shapes
import QtQuick.Controls.Basic
Rectangle {
    id: rect
    property real from: -1.0
    property real to:   1.0
    property real value: 0.0
    property real position: 0
    function remap(x, x1, x2, y1, y2) {
        // 防止除以零
        if (Math.abs(x2 - x1) < 0.000001) return y1

        // 线性映射公式
        return y1 + (y2 - y1) * ((x - x1) / (x2 - x1))
    }
    Component.onCompleted: {
        position = height - 1
        position = remap(value, from, to, height - 1, 1)
        console.log("onCompleted from:", from, " to:", to, " value:", value, " position:", position)
    }
    onValueChanged: {
        console.log("onValueChanged from:", from, " to:", to, " value:", value, " position:", position)
        position = remap(value, from, to, height - 1, 1)
        if (position < 1)
            position = 1
        else if (height - 1 < position)
            position = height - 1
    }
    onFromChanged: {
        console.log("onFromChanged from:", from, " to:", to, " value:", value, " position:", position)
    }
    onToChanged: {
       // position = remap(value, from, to, height - 1, 1)
        console.log("onToChanged  from:", from, " to:", to, " value:", value, " position:", position)
    }
    //color: "#000000"
    Shape {
        x: 0
        y: 0
        width: rect.width
        height: 2

        ShapePath {
            strokeWidth: 2          // 线宽
            strokeColor: "#00FF00"    // 线条颜色
            fillColor: "transparent" // 填充颜色（透明）

            // 起点
            startX: 50
            startY: 1

            // 画到终点
            PathLine { x: 0; y: 1 }
            PathLine { x: 0; y: rect.height - 1 }
            PathLine { x: 50; y: rect.height - 1 }
        }

        ShapePath {
            strokeWidth: 2          // 线宽
            strokeColor: "#FF0000"    // 线条颜色
            fillColor: "transparent" // 填充颜色（透明）

            // 起点
            startX: 0
            startY: rect.position

            // 画到终点
            PathLine { x: 50; y: rect.position }
        }
    }
}