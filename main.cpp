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

#include "cpp/corelib.h"
#include "cpp/canvasitem.h"
#include "cpp/pointereater.h"

#include <QtQml>
#include <QApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<CoreLib>("ABLib", 1, 0, "CoreLib");
    qmlRegisterType<CanvasItem>("ABLib", 1, 0, "CanvasItem");

    PointerEater *pointerEater = new PointerEater();
    app.installEventFilter(pointerEater);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("PointerEater", pointerEater);
    engine.load(QUrl("qrc:///qml/Main.qml"));

    return app.exec();
}
