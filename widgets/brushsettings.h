#ifndef BRUSHSETTINGS_H
#define BRUSHSETTINGS_H

#include <QtGui>
#include "../brushengine.h"

class BrushSettings : public QWidget
{
    Q_OBJECT

public:
    BrushSettings(BrushEngine *brushEngine);

private:
    void addSlider(QString name, int minValue, int defaultValue, int maxValue, const char *slot, int row);
    BrushEngine *brush;
    QGridLayout *gridLayout;
    QSignalMapper *signalMapper;
    QMap<QString, int> defaultSlider;

private slots:
    //void resetSlider(const QString &text);
    void resetSlider(const QString &sliderName);
};

#endif // BRUSHSETTINGS_H
