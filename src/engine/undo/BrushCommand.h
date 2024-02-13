#pragma once
#include <QUndoCommand>
#include <QPixmap>

class Canvas;
class Layer;

class BrushCommand : public QUndoCommand {
public:
    BrushCommand(Canvas* canvas, Layer* layer, const QRect& bound, double opacity);

protected:
    void undo() override;
    void redo() override;

private:
    Canvas* m_canvas = nullptr;
    Layer* m_layer = nullptr;
    QRect m_bound;
    double m_opactity = 0;
    QPixmap m_redoPixmap;
    QPixmap m_undoPixmap;
};
