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
    cpp/painteditem.cpp \
    cpp/brushengine.cpp \
    cpp/openraster.cpp \
    cpp/imageprocessor.cpp \
    cpp/corelib.cpp \
    cpp/pointereater.cpp

HEADERS += \
    cpp/painteditem.h \
    cpp/brushengine.h \
    cpp/openraster.h \
    cpp/imageprocessor.h \
    cpp/corelib.h \
    cpp/pointereater.h

OTHER_FILES += \
    qml/main.qml \
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
    qml/components/ListItem.qml \
    qml/components/ListItemComponent.qml \
    qml/brushlib.js \
    qml/components/ToolWindow.qml \
    qml/style.js \
    qml/FileDialog.qml \
    qml/components/SliderText.qml \
    qml/components/VerticalList.qml \
    qml/TopBar.qml \
    qml/style/ButtonStyle.qml

RESOURCES +=
