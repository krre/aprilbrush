TARGET = aprilbrush
QT += qml quick widgets
CONFIG += c++17

SOURCES += \
    core/Utils.cpp \
    engine/BrushEngine.cpp \
    main.cpp \
    cpp/CanvasItem.cpp \
    cpp/Core.cpp \
    cpp/Settings.cpp \
    cpp/TabletEventFilter.cpp \
    ui/Canvas.cpp \
    ui/CanvasTabWidget.cpp \
    ui/Dialog.cpp \
    ui/MainWindow.cpp \
    ui/NewImage.cpp \
    ui/Options.cpp

HEADERS += \
    core/Constants.h \
    core/Utils.h \
    cpp/CanvasItem.h \
    cpp/Core.h \
    cpp/Settings.h \
    cpp/TabletEventFilter.h \
    engine/BrushEngine.h \
    ui/Canvas.h \
    ui/CanvasTabWidget.h \
    ui/Dialog.h \
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
