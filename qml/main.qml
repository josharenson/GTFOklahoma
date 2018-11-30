import QtQuick 2.3
import QtQuick.Window 2.2

Window {
    id: root

    height: 800; width: 800
    visible: true

    color: "lightblue"

    Timer {
        interval: 100
        running: true
        onTriggered: {
            StoreModel.storeName = "Intro Store"
        }
    }

    Connections {
        target: listView
        onCurrentItemChanged: {
            StoreModel.currentCategory = listView.currentCategory
        }
    }

    ListView {
        id: listView

        anchors.fill: parent

        model: StoreModel.categories

        property string currentCategory: model[currentIndex]
        orientation: ListView.Horizontal
        delegate: Rectangle {
            height: root.height; width: root.width
            color: "teal"

            ListView {
                id: itemsListView

                anchors.centerIn: parent
                width: parent.width
                height: 800

                model: StoreModel

                delegate: Rectangle {
                    anchors.horizontalCenter: parent.horizontalCenter
                    height: 200; width: 400
                    color: "silver"

                    Text {
                        anchors.centerIn: parent
                        text: name
                    }
                }
            }

            Text {
                id: categoryName

                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.margins: 20
                text: modelData
            }

            Rectangle {
                id: leftButton

                height: 40; width: 40
                anchors.bottom: parent.bottom
                anchors.left: parent.left

                color: "red"

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        listView.decrementCurrentIndex()
                    }
                }
            }

            Rectangle {
                id: rightButton

                height: 40; width: 40
                anchors.bottom: parent.bottom
                anchors.right: parent.right

                color: "red"

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        listView.incrementCurrentIndex()
                    }
                }
            }
        }
    }
}
