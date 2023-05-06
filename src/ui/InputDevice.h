#pragma once
#include <QWidget>

class Canvas;
class QLabel;

class InputDevice : public QWidget {
    Q_OBJECT
public:
    enum class Type {
        Mouse,
        Tablet
    };

    struct Data {
        Type type;
        QPointF pos;
        double pressure = 1.0;
    };

    InputDevice(QWidget* parent);

public slots:
   void onDataChanged(const Data& data);

private:
    QLabel* type = nullptr;
    QLabel* posX = nullptr;
    QLabel* posY = nullptr;
    QLabel* pressure = nullptr;
    Canvas* canvas;
};
