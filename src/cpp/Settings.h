#pragma once
#include <QObject>
#include <QSettings>

class Settings : public QObject {
    Q_OBJECT
public:
    explicit Settings(const QString& filePath);
    Q_INVOKABLE void setValue(const QString& group, const QString& key, const QVariant& value);
    Q_INVOKABLE QVariant value(const QString& group, const QString& key, const QVariant& defaultValue = QVariant());

    Q_INVOKABLE void setMap(const QString& group, const QVariantMap& map);
    Q_INVOKABLE QVariantMap map(const QString& group);

    Q_INVOKABLE void setList(const QString& group, const QStringList& list);
    Q_INVOKABLE QStringList list(const QString& group);

private:
    QSettings* settings;

};
