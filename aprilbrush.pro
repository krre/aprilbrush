TARGET = AprilBrush
QT += quick

SOURCES += \
    main.cpp \
    cpp/painteditem.cpp \
    cpp/brushengine.cpp \
    cpp/openraster/openraster.cpp \
    cpp/imageprocessor.cpp

HEADERS += \
    cpp/painteditem.h \
    cpp/brushengine.h \
    cpp/openraster/openraster.h \
    cpp/imageprocessor.h

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
    qml/components/Shadow.qml

#QMAKE_POST_LINK += $$QMAKE_COPY_DIR $$PWD/qml $(DESTDIR) $$escape_expand(\\n\\t)



