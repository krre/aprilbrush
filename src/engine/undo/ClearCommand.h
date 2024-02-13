#pragma once
#include <QUndoCommand>
#include <QPixmap>

class Canvas;
class Layer;

class ClearCommand : public QUndoCommand {
public:
    ClearCommand(Canvas* canvas, Layer* layer);

protected:
    void undo() override;
    void redo() override;

private:
    Canvas* m_canvas = nullptr;
    Layer* m_layer = nullptr;
    QPixmap m_pixmap;
};
