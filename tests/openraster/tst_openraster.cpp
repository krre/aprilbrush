#include <core/OpenRaster.h>
#include <engine/Layer.h>
#include <QTest>
#include <QTemporaryFile>

class TestOpenRaster : public QObject {
    Q_OBJECT
private slots:
    void writeAndRead();
    void readInvalidFile();
};

void TestOpenRaster::writeAndRead() {
    QTemporaryFile tempFile;
    QVERIFY2(tempFile.open(), "Failed to open temporary file");

    QSize imageSize = QSize(100, 100);

    QImage image1(imageSize, QImage::Format_ARGB32);
    image1.fill(Qt::red);

    QPixmap pixmap1 = QPixmap::fromImage(image1);

    Layer layer1("Layer1", pixmap1);
    layer1.setVisible(true);
    layer1.setLocked(false);
    layer1.setSelected(true);

    QImage image2(imageSize, QImage::Format_ARGB32);
    image2.fill(Qt::blue);

    QPixmap pixmap2 = QPixmap::fromImage(image2);

    Layer layer2("Layer2", pixmap2);
    layer2.setVisible(false);
    layer2.setLocked(true);
    layer2.setSelected(false);

    Layers layers;
    layers.append(layer1);
    layers.append(layer2);

    OpenRaster::write(tempFile.fileName(), imageSize, layers);

    Layers readLayers = OpenRaster::read(tempFile.fileName());

    QCOMPARE(readLayers.size(), layers.size());

    for (int i = 0; i < readLayers.size(); ++i) {
        QCOMPARE(readLayers[i].name(), layers[i].name());
        QCOMPARE(readLayers[i].isVisible(), layers[i].isVisible());
        QCOMPARE(readLayers[i].isLocked(), layers[i].isLocked());
        QCOMPARE(readLayers[i].isSelected(), layers[i].isSelected());

        QCOMPARE(readLayers[i].pixmap()->size(), layers[i].pixmap()->size());
    }
}

void TestOpenRaster::readInvalidFile() {
    Layers layers = OpenRaster::read("nonexistent.ora");
    QCOMPARE(layers.size(), 0);
}

QTEST_MAIN(TestOpenRaster)

#include "tst_openraster.moc"
