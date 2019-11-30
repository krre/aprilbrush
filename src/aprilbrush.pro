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
    ui/MainWindow.cpp \
    ui/Options.cpp

HEADERS += \
    core/Constants.h \
    cpp/BrushEngine.h \
    cpp/CanvasItem.h \
    cpp/Core.h \
    cpp/Settings.h \
    cpp/TabletEventFilter.h \
    ui/MainWindow.h \
    ui/Options.h

RESOURCES += \
    qml.qrc \
    js.qrc \
    media.qrc

DISTFILES += \
    changelog.txt \
    README.md
