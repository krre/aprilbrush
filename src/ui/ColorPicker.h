#pragma once
#include <QWidget>
#include <QPixmapCache>
#include <QScopedPointer>

class ColorPicker : public QWidget {
    Q_OBJECT
public:
    ColorPicker();

    const QColor& color() const;

signals:
    void colorChanged(const QColor& color);

public slots:
    void setColor(const QColor& color);

protected:
    void resizeEvent(QResizeEvent*) override;
    void paintEvent(QPaintEvent*) override;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private:
    QPixmap drawWheel() const;
    QPixmap drawTriangle() const;
    void drawWheelSelector();
    void drawTriangleSelector();

    void paintTriangle();
    void paintWheel();

    QColor backGroundColor() const;
    QSize wheelSize() const;
    int outerRadius() const;
    int innerRadius() const;
    qreal triangleEdgeLength() const;

    void setHueAngle(qreal angle);

    QColor coordToColor(const QPoint& coord) const;
    QPoint colorToCoord(const QColor& color) const;

    bool m_hueGrab = false;
    bool m_satValGrab = false;
    QColor m_color;

    QPixmapCache::Key m_wheelKey;
    QPixmapCache::Key m_triangleKey;
};

