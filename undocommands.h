#ifndef UNDOCOMMANDS_H
#define UNDOCOMMANDS_H

#include <QUndoCommand>

class PaintCommand : public QUndoCommand
{
public:
    PaintCommand();
    void undo();
    void redo();

private:

};

class ClearCommand : public QUndoCommand
{
public:
    ClearCommand();
    void undo();
    void redo();

private:

};

#endif // UNDOCOMMANDS_H
