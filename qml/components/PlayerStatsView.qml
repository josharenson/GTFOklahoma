import QtQuick 2.3

ListView {
    id: root

    anchors.fill: parent
    model: PlayerStatsModel ? PlayerStatsModel : null
    onModelChanged: console.log(model)
    delegate: Rectangle {
        height: root.height / 10; width: root.width
        Text {
            anchors.centerIn: parent
            text: stat_name + " : " + value
        }
    }


}
