.import "utils.js" as Utils

function infoMessage(message) {
    return Utils.createDynamicObject(mainRoot, "qrc:/qml/components/messagedialog/MessageDialogInformation.qml", { text: message })
}

function warningMessage(message) {
    return Utils.createDynamicObject(mainRoot, "qrc:/qml/components/messagedialog/MessageDialogWarning.qml", { text: message })
}

function questionMessage(message) {
    return Utils.createDynamicObject(mainRoot, "qrc:/qml/components/messagedialog/MessageDialogQuestion.qml", { text: message })
}

function errorMessage(message) {
    return Utils.createDynamicObject(mainRoot, "qrc:/qml/components/messagedialog/MessageDialogError.qml", { text: message })
}
