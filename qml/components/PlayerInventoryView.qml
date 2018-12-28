import QtQuick 2.3

ListView {
    id: root

    anchors.fill: parent
    model: PlayerInventoryModel ? PlayerInventoryModel : null
    delegate: Rectangle {
        height: root.height / 10; width: root.width
        Text {
            anchors.centerIn: parent
            text: image_url
        }
    }


}
