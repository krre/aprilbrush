#pragma once
#include "CommonTypes.h"

class QSize;

class OpenRaster {
public:
    static void write(const QString& filePath, const QSize& size, const Layers& layers);
    static Layers read(const QString& filePath);
};
