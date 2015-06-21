TARGET = aprilbrush

QT += qml quick widgets
CONFIG += c++11

SOURCES += \
    cpp/tableteventfilter.cpp \
    cpp/corelib.cpp \
    cpp/main.cpp

HEADERS += \
    cpp/tableteventfilter.h \
    cpp/corelib.h

OTHER_FILES += \
    qml/ColorPicker.qml \
    qml/BrushSettings.qml \
    qml/About.qml \
    qml/utils.js \
    qml/undo.js \
    qml/settings.js \
    qml/BrushLibrary.qml \
    qml/CanvasArea.qml \
    qml/LayerManager.qml \
    qml/UndoManager.qml \
    qml/style.js \
    qml/components/SliderText.qml \
    qml/Main.qml \
    qml/main/Actions.qml \
    qml/main/MainMenu.qml \
    qml/FileDialogBase.qml

RESOURCES += \
    qml.qrc

DISTFILES += \
    qml/enums.js \
    qml/components/Panel.qml \
    qml/BrushEngine.qml \
    qml/Canvas3DArea.qml \
    qml/glcode.js
