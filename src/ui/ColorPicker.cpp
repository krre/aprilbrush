#include "ColorPicker.h"
#include "qmath.h"
#include <QtWidgets>

ColorPicker::ColorPicker() {
    setWindowTitle(tr("Color"));
    setMinimumSize(200, 200);
}

const QColor& ColorPicker::color() const {
    return m_color;
}

void ColorPicker::setColor(const QColor& color) {
    if (color == m_color) return;
    m_color = color;
    emit colorChanged(m_color);
    update();
}

void ColorPicker::resizeEvent(QResizeEvent*) {
    QPixmapCache::remove(m_wheelKey);
    QPixmapCache::remove(m_triangleKey);
    update();
}

void ColorPicker::paintEvent(QPaintEvent*) {
    paintWheel();
    paintTriangle();

    drawWheelSelector();
    drawTriangleSelector();
}

void ColorPicker::mousePressEvent(QMouseEvent* event) {
    QPointF point = event->pos() - rect().center();
    qreal length = qSqrt(qPow(point.x(), 2) + qPow(point.y(), 2));

    if (length >= innerRadius() && length <= outerRadius()) {
        setHueAngle(qAtan2(point.x(), point.y()));
        m_hueGrab = true;
    } else if (length < innerRadius()) {
        setColor(coordToColor(event->pos()));
        m_satValGrab = true;
    }
}

void ColorPicker::mouseMoveEvent(QMouseEvent* event) {
    QPointF point = event->pos() - rect().center();

    if (m_hueGrab) {
        setHueAngle(qAtan2(point.x(), point.y()));
    } else if (m_satValGrab) {
        setColor(coordToColor(event->pos()));
    }
}

void ColorPicker::mouseReleaseEvent(QMouseEvent*) {
    m_hueGrab = false;
    m_satValGrab = false;
}

QPixmap ColorPicker::drawWheel() const {
    QPixmap pixmap(wheelSize());
    pixmap.fill(backGroundColor());

    QPainter painter(&pixmap);
    // Transfer to a logical coordinates with the center of the color wheel at (0, 0)
    painter.setWindow(QRect(QPoint(-outerRadius(), -outerRadius()), wheelSize()));
    painter.setPen(Qt::NoPen);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // Draw the circle, filled the conical gradient of the color ring
    QConicalGradient circleGradient(0, 0, 0);

    for (int hue = 0; hue < 360; hue++) {
        circleGradient.setColorAt(hue / 360.0, QColor::fromHsv(hue, 255, 255));
    }

    painter.setBrush(circleGradient);
    painter.drawEllipse(QPointF(0, 0), outerRadius(), outerRadius());

    // Delete the inner circle to a background window color
    painter.setBrush(backGroundColor());
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(QPointF(0, 0), innerRadius() + 2, innerRadius() + 2);

    return pixmap;
}

QPixmap ColorPicker::drawTriangle() const {
    QImage image(innerRadius() * 2, innerRadius() * 2, QImage::Format_ARGB32);
    // Transparent square
    image.fill(QColor(0, 0, 0, 0));

    QPolygonF polygon { QPointF(innerRadius() * 2, innerRadius()), QPointF(innerRadius() / 2, innerRadius() - triangleEdgeLength() / 2), QPointF(innerRadius() / 2, innerRadius() + triangleEdgeLength() / 2) };

    // Painting the black opacity triangle on the square
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(Qt::black));
    painter.drawPolygon(polygon);

    qreal x = innerRadius() * 3 / 2; // median

    // Pixels of the triangle changes by rules:
    // 1. Hue corner of the triangle located to the east, black corner located to the north and white corner located to the south.
    // 2. In the color area, there is a verical black-white gradient from the north to the south.
    // 3. In the alpha area, there is a linear gradient from hue corner to the black-white border.
    for (int pointX = 0; pointX < innerRadius() * 2; pointX++) {
        if (!qAlpha(image.pixel(pointX, innerRadius()))) continue;

        qreal stepColor = qSqrt(3) / (2 * (2 * innerRadius() - pointX)) * 255;
        qreal color = 0;
        qreal x1 = innerRadius() * 2 - pointX;

        for (int pointY = 0; pointY < innerRadius() * 2; pointY++) {
            if (!qAlpha(image.pixel(pointX, pointY))) continue;

            int roundColor = qRound(color);
            qreal y1 = innerRadius() - pointY;
            qreal y = x * y1 / x1;
            qreal alpha =  qSqrt((qPow(x1, 2) + qPow(y1, 2)) / (qPow(x, 2) + qPow(y, 2))) * 255;
            image.setPixel(pointX, pointY, qRgba(roundColor, roundColor, roundColor, qRound(alpha)));
            color += stepColor;
        }
    }

    return QPixmap::fromImage(image);
}

void ColorPicker::drawWheelSelector() {
    // Draw the hue selector
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::white, 2));
    painter.setViewport((width() - outerRadius() * 2) / 2, (height() - outerRadius() * 2) / 2, outerRadius() * 2, outerRadius() * 2);
    painter.setWindow(-outerRadius(), -outerRadius(), outerRadius() * 2, outerRadius() * 2);
    painter.rotate(360 - m_color.hue());

    QPointF hueSelectorInner(innerRadius() + 3, 0);
    QPointF hueSelectorOuter(outerRadius(), 0);

    painter.drawLine(hueSelectorInner, hueSelectorOuter);
}

void ColorPicker::drawTriangleSelector() {
    // Drawing the sat/val pointer
    QPainter painter(this);
    painter.setViewport(width() / 2 - innerRadius(), height() / 2 - innerRadius(), innerRadius() * 2, innerRadius() * 2);
    painter.setWindow(-innerRadius(), -innerRadius(), innerRadius() * 2, innerRadius() * 2);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // In the white corner, the pointer changed color from white to black
    QColor color = m_color.saturation() < 64 && m_color.value() > 192 ? Qt::black : Qt::white;
    painter.setPen(QPen(color, 2));

    QPointF triangleSelectorPoint = colorToCoord(m_color);
    QPointF correctPoint = QPointF(triangleSelectorPoint.x(), -triangleSelectorPoint.y());
    painter.drawEllipse(correctPoint, 4, 4);
}

void ColorPicker::paintTriangle() {
    QPixmap pixmap;

    if (!QPixmapCache::find(m_triangleKey, &pixmap)) {
        pixmap = drawTriangle();
        m_triangleKey = QPixmapCache::insert(pixmap);
    }

    QPainter painter(this);
    painter.setViewport(width() / 2 - innerRadius(), height() / 2 - innerRadius(), innerRadius() * 2, innerRadius() * 2);
    painter.setWindow(-innerRadius(), -innerRadius(), innerRadius() * 2, innerRadius() * 2);
    painter.rotate(360 - m_color.hue());

    QColor triangleHueColor = QColor::fromHsv(m_color.hue(), 255, 255);

    painter.setBrush(QBrush(triangleHueColor));
    painter.setPen(Qt::NoPen);

    QPolygonF polygon { QPointF(innerRadius(), 0), QPointF(-innerRadius() / 2, -triangleEdgeLength() / 2), QPointF(-innerRadius() / 2, triangleEdgeLength() / 2) };
    // Painting the hue-color triangle
    painter.drawPolygon(polygon);
    // Painting the alpha-mask triangle above hue-color triangle
    painter.drawPixmap(-innerRadius(), -innerRadius(), innerRadius() * 2, innerRadius() * 2, pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // Antialiasing border from hue to black corner
    QPointF startPoint(innerRadius(), 0);
    QPointF endPoint(-innerRadius() / 2, -triangleEdgeLength() / 2);

    QLinearGradient borderGradient(startPoint, endPoint);
    borderGradient.setColorAt(0, triangleHueColor);
    borderGradient.setColorAt(1, QColor::fromHsv(m_color.hue(), 255, 0));
    painter.setPen(QPen(borderGradient, 2.7));
    painter.drawLine(startPoint, endPoint);

    // Antialiasing border from hue to white corner
    startPoint = QPointF(innerRadius(), 0);
    endPoint = QPointF(-innerRadius() / 2, triangleEdgeLength() / 2);
    borderGradient = QLinearGradient(startPoint, endPoint);
    borderGradient.setColorAt(0, triangleHueColor);
    borderGradient.setColorAt(1, Qt::white);
    painter.setPen(QPen(borderGradient, 2.7));
    painter.drawLine(startPoint, endPoint);

    // Antialiasing border from black to white corner
    startPoint = QPointF(-innerRadius() / 2, -triangleEdgeLength() / 2);
    endPoint = QPointF(-innerRadius() / 2, triangleEdgeLength() / 2);
    borderGradient = QLinearGradient(startPoint, endPoint);
    borderGradient.setColorAt(0, Qt::black);
    borderGradient.setColorAt(1, Qt::white);
    painter.setPen(QPen(borderGradient, 2.7));
    painter.drawLine(startPoint, endPoint);
}

void ColorPicker::paintWheel() {
    QPixmap pixmap;

    if (!QPixmapCache::find(m_wheelKey, &pixmap)) {
        pixmap = drawWheel();
        m_wheelKey = QPixmapCache::insert(pixmap);
    }

    QPainter painter(this);
    painter.drawPixmap(width() / 2 - outerRadius(), height() / 2 - outerRadius(), outerRadius() * 2, outerRadius() * 2, pixmap);
}

QColor ColorPicker::backGroundColor() const {
    return QPalette().color(QPalette::Window);
}

QSize ColorPicker::wheelSize() const {
    int diameter = qMin(width(), height());
    return QSize(diameter, diameter);
}

int ColorPicker::outerRadius() const {
    return wheelSize().width() / 2.0;
}

int ColorPicker::innerRadius() const {
    return outerRadius() * 0.8;
}

qreal ColorPicker::triangleEdgeLength() const {
    return innerRadius() * qSqrt(3);
}

void ColorPicker::setHueAngle(qreal angle) {
    int hueColor = angle * 180 / M_PI - 90;
    if (hueColor < 0) hueColor += 360;
    setColor(QColor::fromHsv(hueColor, m_color.saturation(), m_color.value()));
}

QColor ColorPicker::coordToColor(const QPoint& coord) const {
    qreal median = triangleEdgeLength() * qSqrt(3) / 2;
    // Position relative to the widget center
    qreal relX = coord.x() - width() / 2;
    qreal relY = height() / 2 - coord.y();
    // Position relative to the widget center with considering rotating of the wheel
    qreal length = qSqrt(qPow(relX, 2) + qPow(relY, 2));
    // Rotating the triangle so that the black corner pointing to the east
    qreal angle = qAtan2(relY, relX) - (m_color.hue() + 120) * M_PI / 180;
    // Correcting relative position
    relX = length * qCos(angle);
    relY = length * qSin(angle);

    // Value
    qreal x1 = innerRadius() - relX;
    qreal y1 = relY;
    qreal x = median;
    qreal y = y1 * x / x1;
    qreal len1 = qSqrt(qPow(x1, 2) + qPow(y1, 2));
    qreal len = qSqrt(qPow(x, 2) + qPow(y, 2));
    int value = qRound(len1 / len * 255);
    if (value > 255) value = 255;
    if (x1 < 0) value = 0;

    // Saturation
    qreal median1 = innerRadius() - relX;
    y = median1 * 2 / qSqrt(3);
    y1 = y / 2 - relY;
    if (y1 < 0) y1 = 0;

    int saturation = qRound(y1 * 255 / y);
    if (saturation > 255) saturation = 255;
    // Step changing the saturation from 0 to 255 (and back) in black corner
    if (saturation < 0 && y1 > 0) saturation = 255;
    if (saturation < 0) saturation = 0;

    return QColor::fromHsv(m_color.hue(), saturation, value);
}

QPoint ColorPicker::colorToCoord(const QColor& color) const {
    int saturation = color.saturation();
    int value = color.value();

    qreal y1 = value / 255.0 * triangleEdgeLength();
    qreal relY = triangleEdgeLength() * saturation / 255.0 * value / 255.0;
    relY = y1 / 2.0 - relY;
    qreal median = triangleEdgeLength() * qSqrt(3) / 2;
    qreal relX = innerRadius() - qSqrt((qPow(median, 2) + qPow(triangleEdgeLength() / 2 - triangleEdgeLength() * saturation / 255.0, 2)) * qPow(value / 255.0, 2) - qPow(relY, 2));
    qreal length = qSqrt(qPow(relX, 2) + qPow(relY, 2));
    qreal angle = qAtan2(relY, relX) + (m_color.hue() + 120) * M_PI / 180;

    relX = length * qCos(angle);
    relY = length * qSin(angle);

    return QPoint(qRound(relX), qRound(relY));
}
