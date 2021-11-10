#include "Canvas.h"
#include "InputDevice.h"
#include "ColorPicker.h"
#include "engine/BrushEngine.h"
#include "engine/Layer.h"
#include "core/SignalHub.h"
#include "core/Context.h"
#include "core/OpenRaster.h"
#include <QtGui>

Canvas::Canvas(const QSize& size) {
    resize(size);
    addLayer(nextName());
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

void Canvas::save() {
    OpenRaster openRaster;
    openRaster.write(m_filePath, size(), layers);
}

void Canvas::open(const QString& filePath) {
    OpenRaster openRaster;
    layers = openRaster.read(filePath);

    m_filePath = filePath;
    m_name = filePathToName(filePath);
}

void Canvas::exportToPng(const QString& filePath) {

}

void Canvas::addLayer(const QString& name) {
    auto newLayer = QSharedPointer<Layer>(new Layer(name, size()));
    layers.append(newLayer);
    m_currentLayerIndex = layers.count() - 1;
}

void Canvas::addLayer(const QSharedPointer<Layer>& layer) {

}

void Canvas::select() {

}

void Canvas::unselect() {

}

void Canvas::setCurrentLayerIndex(int index) {
    m_currentLayerIndex = index;
}

int Canvas::currentLayerIndex() const {
    return m_currentLayerIndex;
}

Layer* Canvas::currentLayer() const {
    return m_currentLayerIndex >= 0 ? layers.at(m_currentLayerIndex).data() : nullptr;
}

QString Canvas::nextName() {
    return tr("Untitled-%1").arg(maxTabCount++);
}

void Canvas::mouseMoveEvent(QMouseEvent* event) {
    paintAction(event->position());
}

void Canvas::mousePressEvent(QMouseEvent* event) {
    paintAction(event->position());
}

void Canvas::mouseReleaseEvent(QMouseEvent*) {
    Context::brushEngine()->unTouch();
}

void Canvas::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event)
    QPainter painter(this);

    for (int i = layers.count() - 1; i >=0; i--) {
        painter.drawPixmap(0, 0, *layers.at(i)->pixmap());
    }
}

void Canvas::paintAction(const QPointF& pos) {
    Context::brushEngine()->paint(layers.at(m_currentLayerIndex)->pixmap(), pos);
    update();

    InputDevice::Data data{};
    data.type = InputDevice::Type::Mouse;
    data.pos = pos;

    emit SignalHub::instance()->inputDeviceDataChanged(data);
}

QString Canvas::filePathToName(const QString& filePath) const {
    return QFileInfo(filePath).fileName().replace(".ora", "");
}
