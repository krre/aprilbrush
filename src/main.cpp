/* AprilBrush - Digital Painting Software
 * Copyright (C) 2012-2014 Vladimir Zarypov <krre31@gmail.com>
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

#include "cpp/qtquick2applicationviewer/qtquick2applicationviewer.h"
#include "cpp/painteditem.h"
#include "cpp/brushengine.h"
#include "cpp/openraster.h"
#include "cpp/imageprocessor.h"
#include "cpp/corelib.h"
#include "cpp/pointereater.h"

#include <QtQuick>
#include <QtQml>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<PaintedItem>("ABLib", 1, 0, "PaintedItem");
    qmlRegisterType<BrushEngine>("ABLib", 1, 0, "BrushEngine");
    qmlRegisterType<OpenRaster>("ABLib", 1, 0, "OpenRaster");
    qmlRegisterType<ImageProcessor>("ABLib", 1, 0, "ImageProcessor");
    qmlRegisterType<CoreLib>("ABLib", 1, 0, "CoreLib");

    PointerEater *pointerEater = new PointerEater();
    app.installEventFilter(pointerEater);

    QtQuick2ApplicationViewer viewer;

    QQmlContext *context = viewer.engine()->rootContext();
    context->setContextProperty("PointerEater", pointerEater);

    viewer.setMainQmlFile(QStringLiteral("qml/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
