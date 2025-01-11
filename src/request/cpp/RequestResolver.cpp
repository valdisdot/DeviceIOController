#include "request/RequestResolver.h"

RequestResolver::RequestResolver(const char* name, bool requireReboot) : requireReboot(requireReboot) {
    this->name = new char[$SYSTEM.SIZE$64];
    copyString(this->name, name, $SYSTEM.SIZE$64);
}

const char* RequestResolver::getName() {
    return name;
}

const bool& RequestResolver::isRebootRequired() {
    return requireReboot;
}
