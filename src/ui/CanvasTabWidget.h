#pragma once
#include "ui/InputDevice.h"
#include <QTabWidget>

class QUndoGroup;

class Canvas;
class BrushEngine;

class CanvasTabWidget : public QTabWidget {
    Q_OBJECT
public:
    CanvasTabWidget(BrushEngine* brushEngine, QUndoGroup* undoGroup);

    Canvas* addCanvas();
    Canvas* addCanvas(const QString& name, const QSize& size);

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

    BrushEngine* m_brushEngine = nullptr;
    QUndoGroup* m_undoGroup = nullptr;
    int m_maxTabCount = 1;
};
