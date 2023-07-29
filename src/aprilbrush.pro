TARGET = aprilbrush
QT += widgets gui-private
CONFIG += c++20

SOURCES += \
    core/EventFilter.cpp \
    core/OpenRaster.cpp \
    engine/BrushEngine.cpp \
    engine/Layer.cpp \
    engine/undo/BrushCommand.cpp \
    engine/undo/ClearCommand.cpp \
    main.cpp \
    ui/BrushSettings.cpp \
    ui/BrushSlider.cpp \
    ui/Canvas.cpp \
    ui/CanvasTabWidget.cpp \
    ui/ColorPicker.cpp \
    ui/Dialog.cpp \
    ui/InputDevice.cpp \
    ui/MainWindow.cpp \
    ui/NewImage.cpp \
    ui/Preferences.cpp

HEADERS += \
    core/CommonTypes.h \
    core/Constants.h \
    core/EventFilter.h \
    core/OpenRaster.h \
    engine/BrushEngine.h \
    engine/Layer.h \
    engine/undo/BrushCommand.h \
    engine/undo/ClearCommand.h \
    ui/BrushSettings.h \
    ui/BrushSlider.h \
    ui/Canvas.h \
    ui/CanvasTabWidget.h \
    ui/ColorPicker.h \
    ui/Dialog.h \
    ui/InputDevice.h \
    ui/MainWindow.h \
    ui/NewImage.h \
    ui/Preferences.h

RESOURCES += \
    resources.qrc \
    media.qrc

DISTFILES += \
    ../Changelog.md \
    ../README.md \
    i18n/aprilbrush-ru.ts

TRANSLATIONS = i18n/aprilbrush-ru.ts
