TARGET = aprilbrush

QT += qml quick widgets

SOURCES += \
    main.cpp \
    cpp/corelib.cpp \
    cpp/pointereater.cpp

HEADERS += \
    cpp/corelib.h \
    cpp/pointereater.h

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
    qml/components/CloseButton.qml \
    qml/UndoManager.qml \
    qml/components/ToolWindow.qml \
    qml/style.js \
    qml/FileDialog.qml \
    qml/components/SliderText.qml \
    qml/TopBar.qml \
    qml/style/ButtonStyle.qml \
    qml/Main.qml

RESOURCES += \
    resources.qrc
