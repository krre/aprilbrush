TARGET = AprilBrush
QT += declarative

SOURCES += \
    main.cpp \
    paintspace.cpp \
    qtquickwindow.cpp \
    brushengine.cpp

HEADERS += \
    paintspace.h \
    qtquickwindow.h \
    brushengine.h

OTHER_FILES += \
    qml/main.qml

RESOURCES += \
    resources.qrc
