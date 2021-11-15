#pragma once
#include <QWidget>
#include <QPixmapCache>
#include <QScopedPointer>

class ColorPicker : public QWidget {
    Q_OBJECT
public:
    ColorPicker();
    ~ColorPicker();

    const QColor& color() const;
    void setColor(const QColor& color);

signals:
    void colorChanged(const QColor& color);

protected:
    void resizeEvent(QResizeEvent*);
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent* event);

private:
    void drawWheel();
    void paintWheel();
    void drawTriangle();
    void paintTriangle();
    void drawWheelSelector();
    void drawTriangleSelector();
    QColor coordToColor(const QPoint& coord);
    QPoint colorToCoord(const QColor& color);

    QColor backgroundColor = QPalette().color(QPalette::Window);
    qreal scaleInnerWheel = 0.8;
    qreal pi = qAtan2(1, 0) * 2; // 3.14
    qreal edgeTriangle;
    int diameterWheel;
    int innerRadius;
    int outerRadius;
    qreal hueAngle = pi / 2;
    qreal satValAngle;
    qreal hueColor;
    bool hueGrab = false;
    bool satValGrab = false;
    QPointF triangleSelectorPoint;
    QColor m_color;

    QPixmapCache::Key wheelKey;
    QPixmapCache::Key triangleKey;
};
