#include "Settings.h"

void Settings::setApplicationLanguage(const QString& lang) {
    setValue("Application/language", lang);
}

QString Settings::applicationLanguage() const {
    return value("Application/language").toString();
}
