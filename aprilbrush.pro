TARGET = AprilBrush
;DESTDIR = Release
;MOC_DIR = Release/Build
;OBJECTS_DIR = Release/Build
;RCC_DIR = Release/Build

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    canvas.cpp \
    brushengine.cpp \
    widgets/brushsettings.cpp \
    widgets/inputdevices.cpp \
    widgets/colorpicker.cpp \
    undocommands.cpp

HEADERS += \
    mainwindow.h \
    canvas.h \
    brushengine.h \
    widgets/brushsettings.h \
    widgets/inputdevices.h \
    widgets/colorpicker.h \
    undocommands.h

RESOURCES += \
    resources.qrc

