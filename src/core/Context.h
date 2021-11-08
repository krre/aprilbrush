#pragma once
#include <QObject>

class ColorPicker;
class BrushEngine;

class Context : public QObject {
public:
    Context(QObject* parent);

    static void setColorPicker(ColorPicker* colorPicker);
    static ColorPicker* colorPicker();

    static BrushEngine* brushEngine();

private:
    static Context* s_instance;
    static ColorPicker* s_colorPicker;
    BrushEngine* m_brushEngine = nullptr;
};

