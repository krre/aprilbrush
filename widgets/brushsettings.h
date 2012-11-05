#ifndef BRUSHSETTINGS_H
#define BRUSHSETTINGS_H

#include <QtGui>
#include "../brushengine.h"

// nameValues[] = {minValues, defaultValues, maxValues}
const int sizeValues[] = {1, 20, 100};
const int opacityValues[] = {0, 100, 100};

class BrushSettings : public QWidget
{
    Q_OBJECT

public:
    BrushSettings(BrushEngine *brush);

private:
    enum {minValue, defaultValue, maxValue};
    QSlider *sizeSlider;
    QSlider *opacitySlider;

private slots:
    void resetSizeSlider();
    void resetOpacitySlider();

};

#endif // BRUSHSETTINGS_H
