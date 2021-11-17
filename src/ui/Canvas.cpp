#include "Canvas.h"
#include "InputDevice.h"
#include "ColorPicker.h"
#include "engine/BrushEngine.h"
#include "engine/Layer.h"
#include "engine/undo/ClearCommand.h"
#include "core/SignalHub.h"
#include "core/Context.h"
#include "core/OpenRaster.h"
#include <QtGui>

Canvas::Canvas(const QSize& size) {
    resize(size);

    m_undoStack = new QUndoStack(this);
    m_undoStack->setUndoLimit(50);

    addLayer(nextName());

    connect(Context::instance(), &Context::keyPressed, this, &Canvas::onKeyPressed);
    connect(Context::instance(), &Context::keyReleased, this, &Canvas::onKeyReleased);

    connect(Context::brushEngine(), &BrushEngine::sizeChanged, this, &Canvas::drawCursor);
    drawCursor(Context::brushEngine()->size());
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

QUndoStack* Canvas::undoStack() const {
    return m_undoStack;
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

void Canvas::exportPng(const QString& filePath) {
    QPixmap pixmap(width(), height());
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);

    for (int i = layers.count() - 1; i >= 0; i--) {
        painter.drawPixmap(0, 0, *layers.at(i)->pixmap());
    }

    pixmap.save(filePath);
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

void Canvas::clear() {
    m_undoStack->push(new ClearCommand(this, currentLayer()));
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
    if (pickPressed()) {
        pickColor(event->position());
    } else {
        paintAction(event->position());
    }
}

void Canvas::mousePressEvent(QMouseEvent* event) {
    setFocus();

    if (pickPressed()) {
        pickColor(event->position());
    } else {
        paintAction(event->position());
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent*) {
    Context::brushEngine()->finish();
}

void Canvas::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event)
    QPainter painter(this);

    for (int i = layers.count() - 1; i >=0; i--) {
        painter.drawPixmap(0, 0, *layers.at(i)->pixmap());
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

void Canvas::onKeyPressed(QKeyEvent* event) {
    if (event->key() == Qt::Key_Alt) {
        setCursor(Qt::CrossCursor);
    }
}

void Canvas::onKeyReleased(QKeyEvent* event) {
    if (event->key() == Qt::Key_Alt) {
        drawCursor(Context::brushEngine()->size());
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

bool Canvas::pickPressed() const {
    return QGuiApplication::queryKeyboardModifiers().testFlag(Qt::AltModifier);
}

void Canvas::pickColor(const QPointF& pos) {
    QPixmap pixmap(width(), height());
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);

    for (int i = layers.count() - 1; i >= 0; i--) {
        painter.drawPixmap(0, 0, *layers.at(i)->pixmap());
    }

    Context::colorPicker()->setColor(QColor(pixmap.toImage().pixel(qRound(pos.x()), qRound(pos.y()))));
}
