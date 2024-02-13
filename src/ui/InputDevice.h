#pragma once
#include <QWidget>

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
    QLabel* m_type = nullptr;
    QLabel* m_posX = nullptr;
    QLabel* m_posY = nullptr;
    QLabel* m_pressure = nullptr;
};
