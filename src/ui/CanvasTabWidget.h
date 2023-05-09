#pragma once
#include "ui/InputDevice.h"
#include <QTabWidget>

class QUndoGroup;
class BrushEngine;
class EventFilter;

class CanvasTabWidget : public QTabWidget {
    Q_OBJECT
public:
    CanvasTabWidget(QUndoGroup* undoGroup);

    void addCanvas(BrushEngine* brushEngine, EventFilter* eventFilter);
    void addCanvas(const QString& name, const QSize& size, BrushEngine* brushEngine, EventFilter* eventFilter);

    QString nextName();

public slots:
    void closeCanvas(int index);

signals:
    void countChanged(int count);
    void inputDeviceDataChanged(const InputDevice::Data& data);

private slots:
    void onCurrentChanged(int index);

private:
    int m_maxTabCount = 1;
    QUndoGroup* m_undoGroup;
};
