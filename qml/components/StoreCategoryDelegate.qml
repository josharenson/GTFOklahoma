import QtQuick 2.3

Item {
    id: root

    property string categoryName
    property var itemModel
    property int modelCount
    property int myIndex

    signal leftClicked()
    signal rightClicked()

    QtObject {
        id: d

        readonly property int buttonHeight: 60
        readonly property int buttonMargins: 20
        readonly property int buttonwidth: 60
    }

    ListView {
        id: itemsListView

        height: 800; width: parent.width
        anchors.top: parent.top
        anchors.bottom: footer.top

        model: root.itemModel
        delegate: ItemCategoryDelegate {
            height: 100; width: parent.width
            itemName: name
        }
    }

    Item {
        id: footer

        width: parent.width
        anchors.bottom: parent.bottom

        Text {
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.margins: 20

            text: root.categoryName
        }

        Image {
            id: leftArrow

            height: d.buttonHeight; width: d.buttonwidth

            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.margins: d.buttonMargins

            source: "../assets/left_arrow.png"

            visible: myIndex > 0

            MouseArea {
                anchors.fill: parent
                onClicked: root.leftClicked()
            }
        }

        Image {
            id: rightArrow

            height: d.buttonHeight; width: d.buttonwidth

            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.margins: d.buttonMargins

            source: "../assets/right_arrow.png"

            visible: myIndex < modelCount - 1

            MouseArea {
                anchors.fill: parent
                onClicked: root.rightClicked()
            }
        }
    }
}
