#pragma once
#include <QWidget>

class Settings;

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

    InputDevice(Settings* settings, QWidget* parent);

public slots:
    void setData(const Data& data);

protected:
    void closeEvent(QCloseEvent* event) override;

private:
    void readSettings();
    void writeSettings();

    Settings* m_settings = nullptr;

    QLabel* m_type = nullptr;
    QLabel* m_position = nullptr;
    QLabel* m_pressure = nullptr;
};
