TARGET = aprilbrush

QT += qml quick widgets
CONFIG += c++11

SOURCES += \
    src/cpp/main.cpp \
    src/cpp/BrushEngine.cpp \
    src/cpp/CanvasItem.cpp \
    src/cpp/Core.cpp \
    src/cpp/Settings.cpp \
    src/cpp/TabletEventFilter.cpp

HEADERS += \
    src/cpp/BrushEngine.h \
    src/cpp/CanvasItem.h \
    src/cpp/Core.h \
    src/cpp/Settings.h \
    src/cpp/TabletEventFilter.h

RESOURCES += \
    src/qml.qrc \
    src/js.qrc \
    src/media.qrc

DISTFILES += \
    changelog.txt \
    README.md

