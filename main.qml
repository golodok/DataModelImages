import QtQuick 2.8
import QtQuick.Window 2.3
import QtQuick.Controls 2.0

Rectangle{
    width:420
    height: 430
    visible:  true
    Drag.active: dragArea.held

    Component{
        id: imgDelegate

        Item
        {
            id: wrapper
            width: itemImage.width
            height: itemImage.height

            Text
            {
                text: myText
            }
            Image  {
                id: itemImage
                width: 90
                height:90
                smooth: true
                fillMode: Image.PreserveAspectFit
                source: pathToImg
            }
        }

    }

    GridView{

        id:grid
        interactive: false
        anchors.fill: parent
        visible: false
        anchors.margins: 10
        cellWidth: 100
        cellHeight: 100
        model:imgModel
        delegate: imgDelegate

    }
    ListView{
        visible: false
        id:listView
        anchors.fill: parent
        anchors.margins: 10
        model:imgModel
        delegate: imgDelegate
    }
    Path{
        id:itemsPath
        startX: 0
        startY: 80
        PathLine {x:500;y:80}
    }

    PathView{
        id:pathView
        visible: true
        anchors.fill: parent
        anchors.margins: 10
        model:imgModel
        delegate: imgDelegate
        path: itemsPath
        pathItemCount: 4

    }

    Button{
        x :400
        y:225
        text: "Список"
        onClicked: {
            grid.visible = false
            pathView.visible = false
            listView.visible = true

        }
    }
    Button{
        x :400
        y:265
        id: buttonGrid
        text: "Таблица"
        onClicked: {
            grid.visible = true
            listView.visible = false
            pathView.visible = false

        }
    }
    Button{
        x :400
        y:300
        id: buttonPath
        text: "Слайд"
        onClicked: {
            grid.visible = false
            listView.visible = false
            pathView.visible = true
        }
    }



}

