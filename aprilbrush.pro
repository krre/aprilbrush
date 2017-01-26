TARGET = aprilbrush

QT += qml quick widgets
CONFIG += c++11

SOURCES += \
    src/cpp/main.cpp \
    src/cpp/BrushEngine.cpp \
    src/cpp/CanvasItem.cpp \
    src/cpp/Core.cpp \
    src/cpp/Settings.cpp \
    src/cpp/TabletEventFilter.cpp

HEADERS += \
    src/cpp/BrushEngine.h \
    src/cpp/CanvasItem.h \
    src/cpp/Core.h \
    src/cpp/Settings.h \
    src/cpp/TabletEventFilter.h

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
    src/js/dialog.js \
    src/qml/components/WindowDialog.qml \
    src/qml/components/ButtonBase.qml \
    src/qml/main/Options.qml \
    src/qml/main/NewImage.qml \
    src/qml/components/ColorBox.qml \
    src/js/brush-lib.js \
    src/qml/components/MessageDialogBase.qml \
    src/qml/components/style/MainTabViewStyle.qml
