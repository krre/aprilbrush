TARGET = AprilBrush
QT += quick

CONFIG(debug, debug|release) {
    DDIR = $$OUT_PWD/debug
}
CONFIG(release, debug|release) {
    DDIR = $$OUT_PWD/release
}

ab.path = $$DDIR
ab.files += qml brushlib

INSTALLS += ab

SOURCES += \
    main.cpp \
    cpp/painteditem.cpp \
    cpp/brushengine.cpp \
    cpp/openraster/openraster.cpp \
    cpp/imageprocessor.cpp \
    cpp/corelib.cpp

HEADERS += \
    cpp/painteditem.h \
    cpp/brushengine.h \
    cpp/openraster/openraster.h \
    cpp/imageprocessor.h \
    cpp/corelib.h

OTHER_FILES += \
    qml/main.qml \
    qml/ColorPicker.qml \
    qml/BrushSettings.qml \
    qml/utils.js \
    qml/undo.js \
    qml/components/Window.qml\
    qml/components/Slider.qml \
    qml/components/CheckerBoard.qml \
    qml/BrushLibrary.qml \
    qml/CanvasArea.qml \
    qml/LayerManager.qml \
    qml/PageManager.qml \
    qml/components/CloseButton.qml \
    qml/components/Button.qml \
    qml/UndoManager.qml \
    qml/components/ListItem.qml \
    qml/components/ListItemComponent.qml \
    qml/components/FileDialog.qml \
    qml/components/Shadow.qml \
    qml/layer.js \
    qml/brushlib.js
