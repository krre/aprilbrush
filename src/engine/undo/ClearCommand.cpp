#include "ClearCommand.h"
#include "ui/Canvas.h"
#include "engine/Layer.h"
#include <QPixmap>

ClearCommand::ClearCommand(Canvas* canvas, Layer* layer) :
        m_canvas(canvas), m_layer(layer) {
    setText(QObject::tr("Clear"));
}

void ClearCommand::undo() {
    m_layer->setPixmap(m_pixmap);
    m_canvas->update();
}

void ClearCommand::redo() {
    m_pixmap = *m_layer->pixmap();
    m_layer->clear();
    m_canvas->update();
}
