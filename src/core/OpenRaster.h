#pragma once
#include "CommonTypes.h"

class OpenRaster {
public:
    OpenRaster();

    void write(const QString& filePath, const QSize& size, const Layers& layers);
    Layers read(const QString& filePath);
};

