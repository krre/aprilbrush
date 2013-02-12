TARGET = AprilBrush
QT += quick

SOURCES += \
    main.cpp \
    paintspace.cpp \
    brushengine.cpp \
    qmlwindow.cpp

HEADERS += \
    qmlwindow.h \
    paintspace.h \
    brushengine.h

OTHER_FILES += \
    qml/main.qml \
    qml/PagePanel.qml \
    qml/FilePanel.qml \
    qml/ColorPicker.qml

QMAKE_POST_LINK += $$QMAKE_COPY_DIR $$PWD/qml $(DESTDIR) $$escape_expand(\\n\\t)
QMAKE_POST_LINK += $$QMAKE_COPY_DIR $$PWD/svg $(DESTDIR) $$escape_expand(\\n\\t)



