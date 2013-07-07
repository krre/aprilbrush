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

#include <QGuiApplication>
#include <QQuickView>
#include <QtQml>
#include <QDebug>
#include <QScreen>

int main(int argc, char *argv[])
{
    // Set GUI multi-threaded while it disabled in Qt 5 on the Windows systems
    qputenv("QML_FORCE_THREADED_RENDERER", "1");

    QGuiApplication app(argc, argv);

    qmlRegisterType<PaintedItem>("AprilBrushLib", 1, 0, "PaintedItem");
    qmlRegisterType<BrushEngine>("AprilBrushLib", 1, 0, "BrushEngine");
    qmlRegisterType<OpenRaster>("AprilBrushLib", 1, 0, "OpenRaster");
    qmlRegisterType<ImageProcessor>("AprilBrushLib", 1, 0, "ImageProcessor");
    qmlRegisterType<CoreLib>("AprilBrushLib", 1, 0, "CoreLib");

    QQuickView view;
    view.setTitle("AprilBrush");
    QScreen *screen = view.screen();
    CoreLib::m_screenSize = screen->size();
    view.setSource(QUrl::fromLocalFile("qml/main.qml"));
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.show();

    return app.exec();
}
