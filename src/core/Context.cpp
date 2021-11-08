#include "Context.h"
#include "engine/BrushEngine.h"
#include "ui/ColorPicker.h"

Context* Context::s_instance = nullptr;
ColorPicker* Context::s_colorPicker = nullptr;

Context::Context(QObject* parent) : QObject(parent) {
    s_instance = this;
    m_brushEngine = new BrushEngine(this);
}

void Context::setColorPicker(ColorPicker* colorPicker) {
    s_colorPicker = colorPicker;
    connect(s_colorPicker, &ColorPicker::colorChanged, s_instance->m_brushEngine, &BrushEngine::setColor);
}

ColorPicker* Context::colorPicker() {
    return s_colorPicker;
}

BrushEngine* Context::brushEngine() {
    return s_instance->m_brushEngine;
}
