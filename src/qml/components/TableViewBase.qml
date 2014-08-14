import QtQuick 2.3
import QtQuick.Controls 1.2

TableView {
    id: root
    property int prevRowCount: 0

    onRowCountChanged: {
        // при удалении последней строки, если на ней стоял курсор,
        // то он переходит на новую последнюю строку
        if (rowCount < prevRowCount && currentRow == rowCount - 1) {
            selectEndRow()
        // если таблица была пуста, и появились строки,
        // то курсор устанавливается на первую строку
        } else if (rowCount > prevRowCount && prevRowCount == 0) {
            selectBeginRow()
        }

        prevRowCount = rowCount
    }

    function selectRow(row) {
        selection.clear()
        if (row >= 0 && rowCount > 0) {
            currentRow = row
            selection.select(row)
        } else {
            currentRow = -1
        }
    }

    function selectBeginRow() {
        selectRow(0)
    }

    function selectEndRow() {
        selectRow(rowCount - 1)
    }
}

