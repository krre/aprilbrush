#pragma once
#include "core/CommonTypes.h"
#include <QWidget>
#include <QScopedPointer>

class Canvas : public QWidget {
    Q_OBJECT
public:
    explicit Canvas(const QSize& size);
    ~Canvas();

    void setName(const QString& name);
    const QString& name() const;

    void setFilePath(const QString& filePath);
    const QString& filePath() const;

    void save();
    void open(const QString& filePath);
    void exportPng(const QString& filePath);

    void addLayer(const QString& name = QString());
    void addLayer(const QSharedPointer<Layer>& layer);

    void select();
    void unselect();

    void clear();

    void setCurrentLayerIndex(int index);
    int currentLayerIndex() const;

    Layer* currentLayer() const;

    QString nextName();

protected:
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent*) override;

    void paintEvent(QPaintEvent* event) override;

private:
    void paintAction(const QPointF& pos);
    QString filePathToName(const QString& filePath) const;

    bool pickPressed() const;
    void pickColor(const QPointF& pos);

    Layers layers;
    int m_currentLayerIndex = -1;
    int maxTabCount = 1;
    QString m_name;
    QString m_filePath;
};
