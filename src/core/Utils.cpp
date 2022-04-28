#include "Utils.h"
#include <QtGui>

Utils::Utils() {

}

QSize Utils::defaultCanvasSize() {
    return QGuiApplication::screens().constFirst()->size();
}
