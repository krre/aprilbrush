TARGET = AprilBrush
QT += quick

SOURCES += \
    main.cpp \
#    paintspace.cpp \
#    qtquickwindow.cpp \
#    brushengine.cpp
    qmlwindow.cpp

HEADERS += \
#    paintspace.h \
#    qtquickwindow.h \
#    brushengine.h
    qmlwindow.h

OTHER_FILES += \
    qml/main.qml \
    qml/PagePanel.qml \
    qml/FilePanel.qml \
    qml/ColorPicker.qml

RESOURCES += \
    resources.qrc
