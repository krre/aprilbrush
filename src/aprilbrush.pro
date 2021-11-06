TARGET = aprilbrush
QT += widgets gui-private
CONFIG += c++17

SOURCES += \
    core/Core.cpp \
    core/TabletEventFilter.cpp \
    core/Utils.cpp \
    engine/BrushEngine.cpp \
    engine/Layer.cpp \
    main.cpp \
    ui/Canvas.cpp \
    ui/CanvasTabWidget.cpp \
    ui/Dialog.cpp \
    ui/MainWindow.cpp \
    ui/NewImage.cpp \
    ui/Options.cpp

HEADERS += \
    core/Constants.h \
    core/Core.h \
    core/TabletEventFilter.h \
    core/Utils.h \
    engine/BrushEngine.h \
    engine/Layer.h \
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
