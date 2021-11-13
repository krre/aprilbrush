#pragma once
#include <QObject>

class QKeyEvent;
class ColorPicker;
class BrushEngine;

class Context : public QObject {
    Q_OBJECT
public:
    Context(QObject* parent);

    static Context* instance();

    static void setColorPicker(ColorPicker* colorPicker);
    static ColorPicker* colorPicker();

    static BrushEngine* brushEngine();

signals:
    void keyPressed(QKeyEvent* event);
    void keyReleased(QKeyEvent* event);

private:
    static Context* s_instance;
    static ColorPicker* s_colorPicker;
    BrushEngine* m_brushEngine = nullptr;
};

