/* AprilBrush - Digital Painting Software
 * Copyright (C) 2012-2013 Vladimir Zarypov <krre@mail.ru>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "cpp/painteditem.h"
#include "cpp/brushengine.h"
#include "cpp/openraster.h"
#include "cpp/imageprocessor.h"
#include "cpp/corelib.h"

#include <QApplication>
#include <QtQuick>
#include <QtQml>
//#include <QtGui>
//#include <QtCore>
//#include <QDebug>
//#include <QScreen>

int main(int argc, char *argv[])
{
    // Set GUI multi-threaded while it disabled in Qt 5 on the Windows systems
    qputenv("QML_FORCE_THREADED_RENDERER", "1");

    qmlRegisterType<PaintedItem>("ABLib", 1, 0, "PaintedItem");
    qmlRegisterType<BrushEngine>("ABLib", 1, 0, "BrushEngine");
    qmlRegisterType<OpenRaster>("ABLib", 1, 0, "OpenRaster");
    qmlRegisterType<ImageProcessor>("ABLib", 1, 0, "ImageProcessor");
    qmlRegisterType<CoreLib>("ABLib", 1, 0, "CoreLib");

    //    QScreen *screen = window->screen();
    CoreLib::m_screenSize = QSize(1000, 600);

    QApplication app(argc, argv);
    QQmlApplicationEngine engine(QUrl(QString("qrc:/qml/main.qml")));
    QObject *topLevel = engine.rootObjects().value(0);
    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);
    if (!window) {
        qWarning("Error: Your root item has to be a Window.");
        return -1;
    }

    window->show();
    return app.exec();
}
