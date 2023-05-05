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

signals:
    void colorChanged(const QColor& color);

public slots:
    void setColor(const QColor& color);

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
    qreal edgeTriangle;
    int diameterWheel;
    int innerRadius;
    int outerRadius;
    qreal hueAngle = M_PI_2;
    qreal satValAngle;
    qreal hueColor;
    bool hueGrab = false;
    bool satValGrab = false;
    QPointF triangleSelectorPoint;
    QColor m_color;

    QPixmapCache::Key wheelKey;
    QPixmapCache::Key triangleKey;
};

