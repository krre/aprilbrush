#pragma once
#include "ui/InputDevice.h"
#include <QTabWidget>

class QUndoGroup;

class Canvas;
class BrushEngine;
class EventFilter;

class CanvasTabWidget : public QTabWidget {
    Q_OBJECT
public:
    CanvasTabWidget(QUndoGroup* undoGroup);

    Canvas* addCanvas(BrushEngine* brushEngine);
    Canvas* addCanvas(const QString& name, const QSize& size, BrushEngine* brushEngine);

    QString nextName();

public slots:
    void closeCurrent();
    void closeAll();
    void closeOthers();

signals:
    void countChanged(int count);
    void inputDeviceDataChanged(const InputDevice::Data& data);

private slots:
    void onCurrentChanged(int index);

private:
    void closeByIndex(int index);

    int m_maxTabCount = 1;
    QUndoGroup* m_undoGroup = nullptr;
};
