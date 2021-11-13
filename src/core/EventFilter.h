#pragma once
#include <QObject>

class EventFilter : public QObject {
    Q_OBJECT
public:
    explicit EventFilter(QObject* parent = nullptr);
    bool eventFilter(QObject* watched, QEvent* event) override;
};

