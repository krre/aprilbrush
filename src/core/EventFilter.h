#pragma once
#include <QObject>

class QKeyEvent;

class EventFilter : public QObject {
    Q_OBJECT
public:
    explicit EventFilter(QObject* parent = nullptr);
    bool eventFilter(QObject* watched, QEvent* event) override;

signals:
    void keyPressed(QKeyEvent* event);
    void keyReleased(QKeyEvent* event);
};

