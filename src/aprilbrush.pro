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
    qml/UndoManager.qml \
    qml/components/ToolWindow.qml \
    qml/style.js \
    qml/components/SliderText.qml \
    qml/Main.qml \
    qml/main/Actions.qml \
    qml/style/MainTabViewStyle.qml \
    qml/main/MainToolBar.qml \
    qml/main/MainMenu.qml \
    qml/main/MainStatusBar.qml \
    qml/components/TableViewBase.qml \
    qml/FileDialogBase.qml

RESOURCES += \
    qml.qrc
