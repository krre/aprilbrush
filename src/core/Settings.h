#pragma once
#include <QSettings>
#include <QSize>

class Settings {
public:
    template <typename T>
    class Key {
    public:
        using value_type = T;

        Key(const QString& key, T defaultValue = T{}) : m_key(key), m_default(defaultValue) {}

        const QString& key() const { return m_key; }
        T defaultValue() const { return m_default; }

    private:
        QString m_key;
        T m_default;
    };

    static void init() {
        #ifdef Q_OS_WIN
            QSettings::setDefaultFormat(QSettings::IniFormat);
        #endif
    }

    template <typename K>
    static void setValue(K::value_type value) {
        QSettings settings;
        settings.setValue(K().key(), value);
    }

    template <typename K>
    static K::value_type value() {
        K key;
        QSettings settings;
        return settings.value(key.key(), key.defaultValue()).template value<typename K::value_type>();
    }

    template <typename K>
    static bool contains() {
        QSettings settings;
        return settings.contains(K().key());
    }
};

namespace General {

struct Geometry : public Settings::Key<QByteArray> {
    Geometry() : Key("geometry") {}
};

struct Language : public Settings::Key<QString> {
    Language() : Key("language") {}
};

}

namespace NewImageKey {

struct Size : public Settings::Key<QSize> {
    Size() : Key("NewImage/size") {}
};

}
