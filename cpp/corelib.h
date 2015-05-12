#ifndef CORELIB_H
#define CORELIB_H

#include <QtCore>
#include <QtGui>

class CoreLib : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QWindow *window READ getWindow WRITE setWindow)
    Q_PROPERTY(QString buildDate READ getBuildDate CONSTANT)

public:
    explicit CoreLib(QObject *parent = 0);
    Q_INVOKABLE QVariant loadSettings();
    Q_INVOKABLE void saveSettings(QVariant settings);
    //Q_INVOKABLE void buildDate() { qDebug() << QLocale(QLocale::C).toDate(QString(__DATE__).simplified(), QLatin1String("MMM d yyyy")); }
    Q_INVOKABLE void writeOra(const QUrl oraPath, const QSize imageSize, const QVariantList layerList);
    Q_INVOKABLE QVariantList readOra(const QUrl oraPath);
    Q_INVOKABLE void setCursorShape(QString type, int size=0);
    Q_INVOKABLE void addEventFilter(QVariant item);
    void setWindow(QWindow *window) { this->window = window; }
    QWindow * getWindow() { return this->window; }
    QString getBuildDate() { return QString(__DATE__); }

private:
    QPointer<QWindow> window;

};

#endif // CORELIB_H
