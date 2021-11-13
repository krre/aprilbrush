TARGET = aprilbrush
QT += widgets gui-private
CONFIG += c++17

SOURCES += \
    core/Context.cpp \
    core/Core.cpp \
    core/EventFilter.cpp \
    core/OpenRaster.cpp \
    core/SignalHub.cpp \
    core/TabletEventFilter.cpp \
    core/Utils.cpp \
    engine/BrushEngine.cpp \
    engine/Layer.cpp \
    main.cpp \
    ui/BrushSettings.cpp \
    ui/Canvas.cpp \
    ui/CanvasTabWidget.cpp \
    ui/ColorPicker.cpp \
    ui/Dialog.cpp \
    ui/InputDevice.cpp \
    ui/MainWindow.cpp \
    ui/NewImage.cpp \
    ui/Options.cpp

HEADERS += \
    core/CommonTypes.h \
    core/Constants.h \
    core/Context.h \
    core/Core.h \
    core/EventFilter.h \
    core/OpenRaster.h \
    core/SignalHub.h \
    core/TabletEventFilter.h \
    core/Utils.h \
    engine/BrushEngine.h \
    engine/Layer.h \
    ui/BrushSettings.h \
    ui/Canvas.h \
    ui/CanvasTabWidget.h \
    ui/ColorPicker.h \
    ui/Dialog.h \
    ui/InputDevice.h \
    ui/MainWindow.h \
    ui/NewImage.h \
    ui/Options.h

RESOURCES += \
    resources.qrc \
    qml.qrc \
    js.qrc \
    media.qrc

DISTFILES += \
    i18n/app-ru.ts \
    ../README.md \
    ../changelog.txt

TRANSLATIONS = i18n/app-ru.ts
