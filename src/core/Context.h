#pragma once
#include <QObject>

class ColorPicker;

class Context : public QObject {
public:
    Context(QObject* parent);

    static void setColorPicker(ColorPicker* colorPicker);
    static ColorPicker* colorPicker();

private:
    static ColorPicker* s_colorPicker;
};

