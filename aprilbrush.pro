TARGET = aprilbrush

QT += qml quick widgets
CONFIG += c++11

SOURCES += \
    src/cpp/tableteventfilter.cpp \
    src/cpp/corelib.cpp \
    src/cpp/main.cpp \
    src/cpp/canvasitem.cpp \
    src/cpp/settings.cpp \
    src/cpp/brushengine.cpp

HEADERS += \
    src/cpp/tableteventfilter.h \
    src/cpp/corelib.h \
    src/cpp/canvasitem.h \
    src/cpp/settings.h \
    src/cpp/brushengine.h

RESOURCES += \
    src/qml.qrc \
    src/js.qrc \
    src/media.qrc

DISTFILES += \
    src/qml/components/SliderText.qml \
    src/qml/main/Actions.qml \
    src/qml/main/MainMenu.qml \
    src/qml/components/Panel.qml \
    src/js/utils.js \
    src/js/undo.js \
    src/js/enums.js \
    src/qml/style.js \
    src/qml/main/About.qml \
    src/qml/components/filedialog/FileDialogBase.qml \
    src/qml/main.qml \
    src/qml/dockers/BrushLibrary.qml \
    src/qml/dockers/BrushSettings.qml \
    src/qml/dockers/ColorPicker.qml \
    src/qml/dockers/LayerManager.qml \
    src/qml/dockers/UndoManager.qml \
    src/qml/main/WorkArea.qml \
    src/qml/components/Dummy.qml \
    src/qml/components/filedialog/FileDialogOpen.qml \
    src/qml/components/filedialog/FileDialogSave.qml \
    src/qml/components/filedialog/FileDialogExport.qml \
    changelog.txt \
    README.md \
    src/qml/components/messagedialog/MessageDialogBase.qml \
    src/qml/components/messagedialog/MessageDialogError.qml \
    src/qml/components/messagedialog/MessageDialogInformation.qml \
    src/qml/components/messagedialog/MessageDialogQuestion.qml \
    src/qml/components/messagedialog/MessageDialogWarning.qml \
    src/js/dialog.js \
    src/qml/components/WindowDialog.qml \
    src/qml/components/ButtonBase.qml
