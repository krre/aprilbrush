TARGET = AprilBrush
QT += quick

SOURCES += \
    main.cpp \
    cpp/paintspace.cpp \
    cpp/brushengine.cpp \

HEADERS += \
    cpp/paintspace.h \
    cpp/brushengine.h \

OTHER_FILES += \
    qml/main.qml \
    qml/FilePanel.qml \
    qml/ColorPicker.qml \
    qml/BrushSettings.qml \
    qml/utils.js \
    qml/components/Window.qml\
    qml/components/Slider.qml \
    qml/components/CheckerBoard.qml \
    qml/BrushLibrary.qml \
    qml/CanvasArea.qml \
    qml/LayerManager.qml \
    qml/PageManager.qml

#QMAKE_POST_LINK += $$QMAKE_COPY_DIR $$PWD/qml $(DESTDIR) $$escape_expand(\\n\\t)


