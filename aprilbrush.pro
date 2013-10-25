TARGET = aprilbrush

QT += quick

SOURCES += \
    main.cpp \
    cpp/painteditem.cpp \
    cpp/brushengine.cpp \
    cpp/openraster.cpp \
    cpp/imageprocessor.cpp \
    cpp/corelib.cpp

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
    qml/Dock.qml\
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
