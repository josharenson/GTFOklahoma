import QtQuick 2.3
import QtQuick.Window 2.2

import "./components"

Window {
    id: root

    height: 800; width: 800
    visible: true

    color: "lightblue"

    Timer {
        interval: 100
        running: true
        onTriggered: {
            GameEngine.currentPlayer = "Josh"
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

        anchors.top: root.top
        height: root.height / 2; width: root.width

        model: StoreModel.categories

        property string currentCategory: model[currentIndex] ? model[currentIndex] : ""

        highlightMoveDuration: 500
        interactive: false
        orientation: ListView.Horizontal

        delegate: StoreCategoryDelegate {
            height: root.height; width: root.width

            categoryName: modelData
            itemModel: StoreModel
            modelCount: listView.count
            myIndex: index

            onLeftClicked: listView.decrementCurrentIndex()
            onRightClicked: listView.incrementCurrentIndex()

            visible: index == listView.currentIndex
        }
    }

    /*PlayerInventoryView {
        anchors.top: listView.bottom
        height: root.height / 2; width: root.width
    }*/

    /*PlayerStatsView {
        anchors.top: listView.bottom
        height: root.height / 2; width: root.width
    }*/
}
