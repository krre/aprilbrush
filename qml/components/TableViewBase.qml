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

    function decrementCurrentRow() {
        if (currentRow > 0) {
            currentRow = currentRow - 1
        }
    }

    function incrementCurrentRow() {
        if (currentRow < rowCount - 1) {
            currentRow = currentRow + 1
        }
    }
}
