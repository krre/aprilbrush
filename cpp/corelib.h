#ifndef CORELIB_H
#define CORELIB_H

#include <QObject>
#include <QDebug>
#include <QVariant>
#include <QDate>
#include <QSize>

class CoreLib : public QObject
{
    Q_OBJECT

public:
    explicit CoreLib(QObject *parent = 0);
    Q_INVOKABLE QByteArray loadBrushPack();
    Q_INVOKABLE QVariant loadSettings();
    Q_INVOKABLE void saveSettings(QVariant settings);
    //Q_INVOKABLE void buildDate() { qDebug() << QLocale(QLocale::C).toDate(QString(__DATE__).simplified(), QLatin1String("MMM d yyyy")); }
    Q_INVOKABLE QString buildDate() { return QString(__DATE__); }
    Q_INVOKABLE QSize screenSize() { return m_screenSize; }

    static QSize m_screenSize;
    
signals:
    
public slots:
    
};

#endif // CORELIB_H
