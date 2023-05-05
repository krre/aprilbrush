#pragma once
#include <QObject>

class QKeyEvent;

class Context : public QObject {
    Q_OBJECT
public:
    Context(QObject* parent);

    static Context* instance();

signals:
    void keyPressed(QKeyEvent* event);
    void keyReleased(QKeyEvent* event);

private:
    static Context* s_instance;
};
