#include "BrushCommand.h"
#include "ui/Canvas.h"
#include "engine/Layer.h"
#include <QPainter>

BrushCommand::BrushCommand(Canvas* canvas, Layer* layer, const QRect& bound, double opacity) :
        m_canvas(canvas), m_layer(layer), m_bound(bound), m_opactity(opacity) {
    setText(QObject::tr("Brush"));
}

void BrushCommand::undo() {
    QPainter painter(m_layer->pixmap());
    painter.setCompositionMode(QPainter::CompositionMode_DestinationOut);
    painter.fillRect(m_bound, Qt::black);
    painter.drawPixmap(m_bound.topLeft(), m_undoPixmap);

    m_canvas->update(m_bound);
}

void BrushCommand::redo() {
    if (m_undoPixmap.isNull()) {
        m_undoPixmap = QPixmap(m_layer->pixmap()->copy(m_bound));
    }

    if (m_redoPixmap.isNull()) {
        m_redoPixmap = QPixmap(m_canvas->buffer().copy(m_bound));
    } else {
        QPainter painter(m_layer->pixmap());
        painter.setOpacity(m_opactity);
        painter.drawPixmap(m_bound.topLeft(), m_redoPixmap);

        m_canvas->update(m_bound);
    }
}
