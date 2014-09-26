#ifndef BRUSHENGINE_H
#define BRUSHENGINE_H

#include <QtCore>
#include "canvasitem.h"

class BrushEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int size READ size WRITE setSize)
    Q_PROPERTY(int opacity READ opacity WRITE setOpacity)
    Q_PROPERTY(int flow READ flow WRITE setFlow)
    Q_PROPERTY(int spacing READ spacing WRITE setSpacing)
    Q_PROPERTY(int hardness READ hardness WRITE setHardness)
    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(int roundness READ roundness WRITE setRoundness)
    Q_PROPERTY(int angle READ angle WRITE setAngle)
    Q_PROPERTY(int jitter READ jitter WRITE setJitter)
    Q_PROPERTY(int eraser READ eraser WRITE setEraser)

public:
    explicit BrushEngine(QObject *parent = 0);
    Q_INVOKABLE void paint(QPointF point, qreal pressure=1);
    Q_INVOKABLE void setTouch(bool isTouch, CanvasItem *canvas=0);


signals:
    void painted();

public slots:

private:
    int size() {return m_size;}
    void setSize(int size) { m_size = size; setDeltaDab(); }
    int opacity() { return m_opacity; }
    void setOpacity(int opacity) { m_opacity = opacity; }
    int flow() { return m_flow; }
    void setFlow(int flow) { m_flow = flow; }
    int spacing() { return m_spacing; }
    void setSpacing(int spacing) { m_spacing = spacing; setDeltaDab(); }
    int hardness() { return m_hardness; }
    void setHardness(int hardness) { m_hardness = hardness; }
    QColor color() { return m_color; }
    void setColor(QColor color) { m_color = color; }
    int roundness() { return m_roundness; }
    void setRoundness(int roundness) { m_roundness = roundness; }
    int angle() { return m_angle; }
    void setJitter(int jitter) { m_jitter = jitter; }
    int jitter() { return m_jitter; }
    void setAngle(int angle) { m_angle = angle; }
    int eraser() { return m_eraser; }
    void setEraser(int eraser) { m_eraser = eraser; }

    void paintDab(QPointF point, qreal pressure);
    void setDeltaDab();
    QPointF linearCurve(QPointF start, QPointF end, qreal t);
    QPointF bezierCurve(QPointF start, QPointF end, QPointF control, qreal t);

    int m_size;
    int m_opacity;
    int m_flow;
    int m_spacing;
    int m_hardness;
    int m_roundness;
    int m_angle;
    int m_jitter;
    QColor m_color;
    int m_eraser;

    bool isBezier = true;
    bool isFirstPoint;
    qreal deltaDab;
    CanvasItem *canvas;

    QPointF startPoint;
    QPointF endPoint;
    QPointF controlPoint;
    QPointF betweenPoint;
    QPointF lastDrawPoint;
    QList<QPointF> points;
};

#endif // BRUSHENGINE_H
