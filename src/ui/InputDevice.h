#pragma once
#include <QWidget>

class Canvas;
class QLabel;

class InputDevice : public QWidget {
    Q_OBJECT
public:
    InputDevice();

private slots:
   void onInputDeviceValueChanged(const QVariantMap& value);

private:
    QLabel* type = nullptr;
    QLabel* posX = nullptr;
    QLabel* posY = nullptr;
    QLabel* pressure = nullptr;
    Canvas* canvas;
};
