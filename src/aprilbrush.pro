TARGET = aprilbrush

QT += qml quick widgets
CONFIG += c++11

SOURCES += \
    main.cpp \
    cpp/BrushEngine.cpp \
    cpp/CanvasItem.cpp \
    cpp/Core.cpp \
    cpp/Settings.cpp \
    cpp/TabletEventFilter.cpp

HEADERS += \
    cpp/BrushEngine.h \
    cpp/CanvasItem.h \
    cpp/Core.h \
    cpp/Settings.h \
    cpp/TabletEventFilter.h

RESOURCES += \
    qml.qrc \
    js.qrc \
    media.qrc

DISTFILES += \
    changelog.txt \
    README.md
