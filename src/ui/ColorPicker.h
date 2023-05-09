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

    QColor m_backgroundColor = QPalette().color(QPalette::Window);
    qreal m_scaleInnerWheel = 0.8;
    qreal m_edgeTriangle;
    int m_diameterWheel;
    int m_innerRadius;
    int m_outerRadius;
    qreal m_hueAngle = M_PI_2;
    qreal m_satValAngle;
    qreal m_hueColor;
    bool m_hueGrab = false;
    bool m_satValGrab = false;
    QPointF m_triangleSelectorPoint;
    QColor m_color;

    QPixmapCache::Key m_wheelKey;
    QPixmapCache::Key m_triangleKey;
};

