#pragma once
#include <QObject>
#include <QColor>
#include <QPointF>

class CanvasItem;
class QPainter;

class BrushEngine : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool isTouch READ isTouch WRITE setIsTouch NOTIFY isTouchChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(int size READ size WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(int spacing READ spacing WRITE setSpacing NOTIFY spacingChanged)
    Q_PROPERTY(int hardness READ hardness WRITE setHardness NOTIFY hardnessChanged)
    Q_PROPERTY(int opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)
    Q_PROPERTY(int flow READ flow WRITE setFlow NOTIFY flowChanged)
    Q_PROPERTY(int roundness READ roundness WRITE setRoundness NOTIFY roundnessChanged)
    Q_PROPERTY(int angle READ angle WRITE setAngle NOTIFY angleChanged)
    Q_PROPERTY(int jitter READ jitter WRITE setJitter NOTIFY jitterChanged)
    Q_PROPERTY(int eraser READ eraser WRITE setEraser NOTIFY eraserChanged)

public:
    Q_INVOKABLE void paint(const QPointF& point, float pressure=1.0);
    Q_INVOKABLE void setCanvasItem(CanvasItem* m_canvasItem);
    Q_INVOKABLE void setCanvasBuffer(CanvasItem* canvasBuffer) { this->m_canvasBuffer = canvasBuffer; }
    Q_INVOKABLE QByteArray undoImage() { return m_undoImage; }
    Q_INVOKABLE QByteArray redoImage() { return m_redoImage; }
    Q_INVOKABLE QPointF startPos() { return topleft; }

    QColor color() const { return m_color; }
    void setColor(QColor color);
    int size() const { return m_size; }
    void setSize(int size);
    int hardness() const { return m_hardness; }
    void setHardness(int hardness);
    int opacity() const { return m_opacity; }
    void setOpacity(int opacity);
    int flow() const { return m_flow; }
    void setFlow(int flow);
    int roundness() const { return m_roundness; }
    void setRoundness(int roundness);
    int angle() const { return m_angle; }
    void setAngle(int angle);
    int spacing() const { return m_spacing; }
    void setSpacing(int spacing);
    int jitter() const { return m_jitter; }
    void setJitter(int jitter);
    int eraser() const { return m_eraser; }
    void setEraser(int eraser);

    bool isTouch() const { return m_isTouch; }
    void setIsTouch(bool isTouch);

signals:
    void colorChanged(QColor color);
    void sizeChanged(int size);
    void hardnessChanged(int hardness);
    void opacityChanged(int opacity);
    void flowChanged(int flow);
    void roundnessChanged(int roundness);
    void angleChanged(int angle);
    void spacingChanged(int spacing);
    void jitterChanged(int jitter);
    void eraserChanged(int eraser);

    void isTouchChanged(bool isTouch);

private:
    void paintDab(const QPointF& point, QPainter& painter);

    QColor m_color = QColor(Qt::black);
    int m_size = 30;
    int m_hardness = 80;
    int m_opacity = 80;
    int m_flow = 100;
    int m_roundness = 100;
    int m_angle = 0;
    int m_spacing = 100;
    int m_jitter = 0;
    int m_eraser = 0;

    bool m_isTouch = false;
    CanvasItem* m_canvasItem;
    CanvasItem* m_canvasBuffer;

    QPointF startPoint;
    QPointF lastPoint;
    QPoint topleft;
    QPoint bottomright;
    QByteArray m_undoImage;
    QByteArray m_redoImage;
};
