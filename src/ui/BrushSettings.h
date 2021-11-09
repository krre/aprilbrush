#pragma once
#include <QWidget>

class BrushEngine;

class BrushSettings : public QWidget {
    Q_OBJECT
public:
    BrushSettings(BrushEngine* brushEngine);

private:
    QLayout* createSlider(int minValue, int maxValue, int defaultValue, const std::function<void(int)>& brushSlot);

    BrushEngine* m_brushEngine = nullptr;
};
