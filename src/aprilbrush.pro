folder_01.source = images
folder_02.source = presets
folder_03.source = qml
folder_01.target =
folder_02.target =
folder_03.target =
DEPLOYMENTFOLDERS = folder_01 folder_02 folder_03

# Please do not modify the following two lines. Required for deployment.
include(cpp/qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

TARGET = aprilbrush

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

RESOURCES +=
