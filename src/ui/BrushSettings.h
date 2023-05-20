#pragma once
#include <QWidget>

class BrushEngine;

class BrushSettings : public QWidget {
    Q_OBJECT
public:
    BrushSettings(BrushEngine* brushEngine);

private:
    BrushEngine* m_brushEngine = nullptr;
};
