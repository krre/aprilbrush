#include "Context.h"

Context* Context::s_instance = nullptr;

Context::Context(QObject* parent) : QObject(parent) {
    s_instance = this;
}

Context* Context::instance() {
    return s_instance;
}
