#include "undocommands.h"

PaintCommand::PaintCommand(Canvas *canvasOut)
{
    canvas = canvasOut;
    isPaint = false;
}

void PaintCommand::undo()
{
    canvas->setSurface(&prevPixmap);
    canvas->updatePixmap();
    canvas->update();
    setText("Paint");
}

void PaintCommand::redo()
{
    if (!isPaint)
    {
        prevPixmap = canvas->prevSurface();
        pixmap = *(canvas->surface());
        isPaint = true;
        setText("Paint");
    }
    else
    {
        canvas->setSurface(&pixmap);
        canvas->updatePixmap();
        canvas->update();
    }
    setText("Paint");
}

ClearCommand::ClearCommand(Canvas *canvasOut)
{
    canvas = canvasOut;
}

void ClearCommand::undo()
{
    canvas->setSurface(&pixmap);
    canvas->updatePixmap();
    canvas->update();
    setText("Clear");
}

void ClearCommand::redo()
{
    pixmap = *(canvas->surface());
    canvas->surface()->fill(Qt::white);
    canvas->updatePixmap();
    canvas->update();
    setText("Clear");
}
