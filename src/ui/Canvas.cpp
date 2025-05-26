#include "Canvas.h"
#include "InputDevice.h"
#include "engine/BrushEngine.h"
#include "engine/Layer.h"
#include "engine/undo/ClearCommand.h"
#include "engine/undo/BrushCommand.h"
#include "core/OpenRaster.h"
#include <QPainter>
#include <QGuiApplication>
#include <QScreen>
#include <QMouseEvent>
#include <QFileInfo>
#include <ranges>

Canvas::Canvas(const QSize& size, BrushEngine* brushEngine) : m_brushEngine(brushEngine) {
    resize(size);
    m_buffer = QPixmap(size);
    m_buffer.fill(Qt::transparent);

    m_undoStack = new QUndoStack(this);
    m_undoStack->setUndoLimit(50);

    addLayer(nextName());

    connect(brushEngine, &BrushEngine::sizeChanged, this, &Canvas::drawCursor);
    drawCursor(brushEngine->size());
}

Canvas::~Canvas() {

}

void Canvas::setName(const QString& name) {
    m_name = name;
}

const QString& Canvas::name() const {
    return m_name;
}

void Canvas::setFilePath(const QString& filePath) {
    m_filePath = filePath;
    m_name = filePathToName(filePath);
}

const QString& Canvas::filePath() const {
    return m_filePath;
}

const QPixmap& Canvas::buffer() const {
    return m_buffer;
}

QUndoStack* Canvas::undoStack() const {
    return m_undoStack;
}

void Canvas::save() const {
    OpenRaster::write(m_filePath, size(), m_layers);
}

void Canvas::open(const QString& filePath) {
    m_layers = OpenRaster::read(filePath);

    m_filePath = filePath;
    m_name = filePathToName(filePath);
}

void Canvas::exportPng(const QString& filePath) const {
    QPixmap pixmap(width(), height());
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);

    for (auto& layer : m_layers | std::views::reverse) {
        painter.drawPixmap(0, 0, *layer.pixmap());
    }

    pixmap.save(filePath);
}

void Canvas::addLayer(const QString& name) {
    Layer layer(name, size());
    m_layers.append(std::move(layer));
    m_currentLayerIndex = m_layers.count() - 1;
}

void Canvas::select() {

}

void Canvas::unselect() {

}

void Canvas::clear() {
    m_undoStack->push(new ClearCommand(this, currentLayer()));
}

void Canvas::setCurrentLayerIndex(int index) {
    m_currentLayerIndex = index;
}

int Canvas::currentLayerIndex() const {
    return m_currentLayerIndex;
}

Layer* Canvas::currentLayer() {
    return m_currentLayerIndex >= 0 ? &m_layers[m_currentLayerIndex] : nullptr;
}

QString Canvas::nextName() {
    return tr("Untitled-%1").arg(m_maxTabCount++);
}

QSize Canvas::defaultSize() {
    return QGuiApplication::screens().constFirst()->size();
}

void Canvas::mouseMoveEvent(QMouseEvent* event) {
    if (isAltPressed()) {
        pickColor(event->position());
    } else {
        paintAction(event->position());
    }
}

void Canvas::mousePressEvent(QMouseEvent* event) {
    setFocus();

    if (isAltPressed()) {
        pickColor(event->position());
    } else {
        m_paintArea = QRect(event->position().toPoint(), event->position().toPoint());
        paintAction(event->position());
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent*) {
    double opacity = m_brushEngine->opacity() / 100.0;
    m_undoStack->push(new BrushCommand(this, currentLayer(), m_paintArea, opacity));

    QPainter painter(currentLayer()->pixmap());
    painter.setOpacity(opacity);
    painter.drawPixmap(0, 0, m_buffer);

    m_buffer.fill(Qt::transparent);
    m_brushEngine->finish();
    update();
}

void Canvas::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Alt) {
        setCursor(Qt::CrossCursor);
    }
}

void Canvas::keyReleaseEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Alt) {
        drawCursor(m_brushEngine->size());
    }
}

void Canvas::paintEvent(QPaintEvent* event [[maybe_unused]]) {
    QPainter painter(this);

    for (int i = m_layers.count() - 1; i >= 0; --i) {
        if (m_currentLayerIndex == i) {
            painter.setOpacity(m_brushEngine->opacity() / 100.0);
            painter.drawPixmap(0, 0, m_buffer);
        }

        painter.setOpacity(1.0);
        painter.drawPixmap(0, 0, *m_layers[i].pixmap());
    }
}

void Canvas::drawCursor(int size) {
   // Size of the cursor should not be very small
   int sizeBrush = qMax(size, 3);
   QPixmap pixmap(sizeBrush, sizeBrush);
   pixmap.fill(QColor(255, 255, 255, 0));

   QPainter painter(&pixmap);
   painter.setRenderHint(QPainter::Antialiasing, true);
   painter.setBrush(Qt::NoBrush);
   painter.setPen(QColor(0, 0, 0, 200));
   painter.drawEllipse(0, 0, sizeBrush, sizeBrush);
   painter.setPen(QColor(255, 255, 255, 200));
   painter.drawEllipse(1, 1, sizeBrush - 2, sizeBrush - 2);

   setCursor(QCursor(pixmap));
}

void Canvas::paintAction(const QPointF& pos) {
    QRect bound = m_brushEngine->paint(m_brushEngine->eraser() < 50 ? &m_buffer : currentLayer()->pixmap(), pos);

    if (bound.isNull()) return;

    QRect clipedBound = clipBound(bound);
    update(clipedBound);

    m_paintArea.setTopLeft(QPoint(qMin(m_paintArea.topLeft().x(), clipedBound.topLeft().x()), qMin(m_paintArea.topLeft().y(), clipedBound.topLeft().y())));
    m_paintArea.setBottomRight(QPoint(qMax(m_paintArea.bottomRight().x(), clipedBound.bottomRight().x()), qMax(m_paintArea.bottomRight().y(), clipedBound.bottomRight().y())));

    InputDevice::Data data{};
    data.type = InputDevice::Type::Mouse;
    data.position = pos;

    emit inputDeviceDataChanged(data);
}

QString Canvas::filePathToName(const QString& filePath) const {
    return QFileInfo(filePath).fileName().replace(".ora", "");
}

bool Canvas::isAltPressed() const {
    return QGuiApplication::queryKeyboardModifiers().testFlag(Qt::AltModifier);
}

void Canvas::pickColor(const QPointF& pos) {
    QPixmap pixmap(width(), height());
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);

    for (const auto& layer : m_layers | std::views::reverse) {
        painter.drawPixmap(0, 0, *layer.pixmap());
    }

    emit colorPicked(QColor(pixmap.toImage().pixel(qRound(pos.x()), qRound(pos.y()))));
}

QRect Canvas::clipBound(const QRect& bound) const {
    // Correct corner positions on brush size
    int brushSize = m_brushEngine->size();
    QPoint topLeft(bound.topLeft().x() - brushSize, bound.topLeft().y() - brushSize);
    QPoint bottomRight(bound.bottomRight().x() + brushSize, bound.bottomRight().y() + brushSize);

    // Bound to canvas size
    topLeft.setX(qMax(0, topLeft.x()));
    topLeft.setY(qMax(0, topLeft.y()));
    bottomRight.setX(qMin(size().width(), bottomRight.x()));
    bottomRight.setY(qMin(size().height(), bottomRight.y()));

    return QRect(topLeft, bottomRight);
}
