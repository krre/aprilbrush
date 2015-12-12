TARGET = aprilbrush

QT += qml quick widgets
CONFIG += c++11

SOURCES += \
    cpp/tableteventfilter.cpp \
    cpp/corelib.cpp \
    cpp/main.cpp \
    cpp/canvasitem.cpp \
    cpp/settings.cpp \
    cpp/brushengine.cpp

HEADERS += \
    cpp/tableteventfilter.h \
    cpp/corelib.h \
    cpp/canvasitem.h \
    cpp/settings.h \
    cpp/brushengine.h

OTHER_FILES += \
    qml/CanvasArea.qml \
    qml/style.js \
    qml/components/SliderText.qml \
    qml/main/Actions.qml \
    qml/main/MainMenu.qml

RESOURCES += \
    qml.qrc \
    js.qrc \
    media.qrc

DISTFILES += \
    qml/components/Panel.qml \
    qml/BrushEngine.qml \
    qml/Canvas3DArea.qml \
    js/utils.js \
    js/undo.js \
    js/enums.js \
    qml/main/About.qml \
    qml/components/filedialog/FileDialogBase.qml \
    qml/main.qml \
    qml/dockers/BrushLibrary.qml \
    qml/dockers/BrushSettings.qml \
    qml/dockers/ColorPicker.qml \
    qml/dockers/LayerManager.qml \
    qml/dockers/UndoManager.qml \
    qml/main/WorkArea.qml \
    qml/components/Dummy.qml \
    qml/components/filedialog/FileDialogOpen.qml \
    qml/components/filedialog/FileDialogSave.qml \
    qml/components/filedialog/FileDialogExport.qml
