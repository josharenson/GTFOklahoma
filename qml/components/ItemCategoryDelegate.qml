import QtQuick 2.3

Item {
    id: root

    property string itemName

    height: parent.height; width: parent.width

    Text {
        anchors.centerIn: parent
        text: root.itemName
    }

    MouseArea {
        anchors.fill: parent
        onClicked: GameEngine.addItemToInventory(root.itemName)
    }
}
