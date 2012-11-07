#ifndef BRUSHSETTINGS_H
#define BRUSHSETTINGS_H

#include <QtGui>
#include "../brushengine.h"

// nameValues[] = {minValues, defaultValues, maxValues}
const int sizeValues[] = {1, 20, 100};
const int opacityValues[] = {0, 50, 100};
const int spaceValues[] = {1, 25, 500};

class BrushSettings : public QWidget
{
    Q_OBJECT

public:
    BrushSettings(BrushEngine *brush);

private:
    enum {minValue, defaultValue, maxValue};
    QSlider *sizeSlider;
    QSlider *opacitySlider;
    QSlider *spaceSlider;

private slots:
    void resetSizeSlider();
    void resetOpacitySlider();
    void resetSpaceSlider();
};

#endif // BRUSHSETTINGS_H
