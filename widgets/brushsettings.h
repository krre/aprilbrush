#ifndef BRUSHSETTINGS_H
#define BRUSHSETTINGS_H

#include <QtGui>
#include "../brushengine.h"

// nameValues[] = {minValues, defaultValues, maxValues}
const int sizeValues[] = {1, 20, 500};
const int opacityValues[] = {0, 100, 100};

class BrushSettings : public QWidget
{
    Q_OBJECT

public:
    BrushSettings(BrushEngine *brush);

private:
    enum {minValue, defaultValue, maxValue};

};

#endif // BRUSHSETTINGS_H
