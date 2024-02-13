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
        QPointF position;
        double pressure = 1.0;
    };

    InputDevice(QWidget* parent);

public slots:
    void setData(const Data& data);

private:
    QLabel* m_type = nullptr;
    QLabel* m_position = nullptr;
    QLabel* m_pressure = nullptr;
};
