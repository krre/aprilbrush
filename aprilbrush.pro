TARGET = aprilbrush

QT += qml quick widgets
CONFIG += c++11

SOURCES += \
    main.cpp \
    cpp/blend.cpp \
    cpp/tableteventfilter.cpp \
    cpp/brushengine.cpp \
    cpp/canvasitem.cpp \
    cpp/corelib.cpp

HEADERS += \
    cpp/blend.h \
    cpp/tableteventfilter.h \
    cpp/brushengine.h \
    cpp/canvasitem.h \
    cpp/corelib.h

OTHER_FILES += \
    qml/ColorPicker.qml \
    qml/BrushSettings.qml \
    qml/About.qml \
    qml/utils.js \
    qml/undo.js \
    qml/settings.js \
    qml/components/CheckerBoard.qml \
    qml/BrushLibrary.qml \
    qml/CanvasArea.qml \
    qml/LayerManager.qml \
    qml/UndoManager.qml \
    qml/components/ToolWindow.qml \
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
    qml/components/Panel.qml
