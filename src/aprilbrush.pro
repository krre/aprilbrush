TARGET = aprilbrush
QT += qml quick widgets
CONFIG += c++17

SOURCES += \
    main.cpp \
    cpp/BrushEngine.cpp \
    cpp/CanvasItem.cpp \
    cpp/Core.cpp \
    cpp/Settings.cpp \
    cpp/TabletEventFilter.cpp \
    ui/Canvas.cpp \
    ui/CanvasTabWidget.cpp \
    ui/MainWindow.cpp \
    ui/NewImage.cpp \
    ui/Options.cpp

HEADERS += \
    core/Constants.h \
    cpp/BrushEngine.h \
    cpp/CanvasItem.h \
    cpp/Core.h \
    cpp/Settings.h \
    cpp/TabletEventFilter.h \
    ui/Canvas.h \
    ui/CanvasTabWidget.h \
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
