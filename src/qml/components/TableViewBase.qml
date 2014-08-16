import QtQuick 2.3
import QtQuick.Controls 1.2

TableView {
    id: root
    headerVisible: false

    onCurrentRowChanged: {
        selection.clear()
        if (currentRow > -1) {
            selection.select(currentRow)
        }
    }
}

