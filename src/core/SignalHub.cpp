#include "SignalHub.h"

static SignalHub* s_instance = nullptr;

SignalHub::SignalHub() {
    s_instance = this;
}

SignalHub* SignalHub::instance() {
    return s_instance;
}
