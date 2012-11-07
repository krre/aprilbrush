#ifndef BRUSHSETTINGS_H
#define BRUSHSETTINGS_H

#include <QtGui>
#include "../brushengine.h"

class BrushSettings : public QWidget
{
    Q_OBJECT

public:
    BrushSettings(BrushEngine *brush);

private:
    void addSlider(BrushEngine *brush, QGridLayout *layout, QString name,
                   int minValue, int defaultValue, int maxValue, const char *slot, int row);

private slots:
    void resetSlider(QSlider *slider, int defaultValue);
};

#endif // BRUSHSETTINGS_H
