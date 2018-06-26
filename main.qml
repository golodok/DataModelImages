import QtQuick 2.8
import QtQml.Models 2.1
import QtQuick.Controls 2.0

Rectangle{
    width:420
    height: 430
    visible:  true

    Component{
        id: imgDelegate
        Item
        {
            id: dragRect
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
            MouseArea {
                id: mouseArea
                property int visualIndex: imgModel.itemsIndex
                anchors.fill: parent
                drag.target: dragRect
                Drag.source: imgDelegate
            }
            states: [
                State {
                    when: icon.Drag.active
                    ParentChange {
                        target: dragRect
                        parent: imgDelegate
                    }

                    AnchorChanges {
                        target: itemImage;
                        anchors.horizontalCenter: undefined;
                        anchors.verticalCenter: undefined
                    }
                }
            ]
            DropArea {
                anchors { fill: parent; margins: 15 }

                onEntered: imgModel.items.move(drag.source.visualIndex, delegateRoot.visualIndex)
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
        property int dragItemIndex: -1

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

