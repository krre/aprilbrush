#ifndef UNDOCOMMANDS_H
#define UNDOCOMMANDS_H

#include <QUndoCommand>
#include "canvas.h"

class PaintCommand : public QUndoCommand
{
public:
    PaintCommand(Canvas *canvasOut);
    void undo();
    void redo();

private:
    Canvas *canvas;
    QPixmap pixmap;
    QPixmap prevPixmap;
    bool isPaint;

};

class ClearCommand : public QUndoCommand
{
public:
    ClearCommand(Canvas *canvasOut);
    void undo();
    void redo();

private:
    Canvas *canvas;
    QPixmap pixmap;

};

#endif // UNDOCOMMANDS_H
