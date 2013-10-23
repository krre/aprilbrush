TARGET = aprilbrush

QT += quick

ab.path += $$OUT_PWD
ab.files += qml presets

INSTALLS += ab

SOURCES += \
    main.cpp \
    cpp/painteditem.cpp \
    cpp/brushengine.cpp \
    cpp/openraster.cpp \
    cpp/imageprocessor.cpp \
    cpp/corelib.cpp

win32: {
    SOURCES += cpp/wacom/wacom_win.cpp
    HEADERS += cpp/wacom/wacom_win.h
}
unix: {
    SOURCES += cpp/wacom/wacom_unix.cpp
    HEADERS += cpp/wacom/wacom_unix.h
    LIBS += -lXi
}

HEADERS += \
    cpp/painteditem.h \
    cpp/brushengine.h \
    cpp/openraster.h \
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
    qml/UndoManager.qml \
    qml/components/ListItem.qml \
    qml/components/ListItemComponent.qml \
    qml/components/Shadow.qml \
    qml/brushlib.js \

RESOURCES += \
    resources.qrc
