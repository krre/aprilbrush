#pragma once
#include <QWidget>
#include <QScopedPointer>

class BrushEngine;
class Layer;

class Canvas : public QWidget {
    Q_OBJECT
public:
    explicit Canvas(const QSize& size);
    ~Canvas();

    void addLayer(const QString& name = QString());
    void addLayer(const QSharedPointer<Layer>& layer);

    void setCurrentLayerIndex(int index);
    int currentLayerIndex() const;

    Layer* currentLayer() const;

    QString nextName();

protected:
    void mouseMoveEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

private:
    QScopedPointer<BrushEngine> brushEngine;
    QVector<QSharedPointer<Layer>> layers;
    int m_currentLayerIndex = -1;
    int maxTabCount = 1;
};
