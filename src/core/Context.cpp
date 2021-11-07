#include "Context.h"

ColorPicker* Context::s_colorPicker = nullptr;

Context::Context(QObject* parent) : QObject(parent) {

}

void Context::setColorPicker(ColorPicker* colorPicker) {
    s_colorPicker = colorPicker;
}

ColorPicker* Context::colorPicker() {
    return s_colorPicker;
}
