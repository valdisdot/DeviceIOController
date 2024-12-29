#include "capsule/PortState.h"

void PortState::eraseModes() {
    JsonArray modes = holder[SCHEMA_STATE.MODES].as<JsonArray>();
    for (int i = 0; i < CONSTANT.PORT_COUNT; ++i) {
        modes[i] = CONSTANT.MODE_NOT_INITIALIZED;
    }
}

void PortState::eraseData() {
    JsonArray data = holder[SCHEMA_STATE.DATA].as<JsonArray>();
    for (int i = 0; i < CONSTANT.PORT_COUNT; ++i) {
        data[i] = CONSTANT.NO_VALUE_INT;
    }
}

PortState::PortState() {
    JsonArray modes = holder[SCHEMA_STATE.MODES].to<JsonArray>();
    eraseModes();
    JsonArray data = holder[SCHEMA_STATE.DATA].to<JsonArray>();
    eraseData();
}

void PortState::copyModesInto(int* destination) {
    if (destination) {
        JsonArray modes = holder[SCHEMA_STATE.MODES].as<JsonArray>();
        for (int i = 0; i < CONSTANT.PORT_COUNT; ++i) {
            destination[i] = modes[i].as<int>();
        }
    }
}

JsonArrayConst PortState::getModesAsJson() {
    return holder[SCHEMA_STATE.MODES].as<JsonArrayConst>();
}

void PortState::setModes(const int* modes) {
    if (modes) {
        eraseModes();
        JsonArray _modes = holder[SCHEMA_STATE.MODES].as<JsonArray>();
        for (int i = 0; i < CONSTANT.PORT_COUNT; ++i) {
            _modes[i] = modes[i];
        }
    }
}

void PortState::setModes(JsonArrayConst modes) {
    if (modes) {
        eraseModes();
        JsonArray _modes = holder[SCHEMA_STATE.MODES].as<JsonArray>();
        for (int i = 0; i < CONSTANT.PORT_COUNT && i < modes.size(); ++i) {
            _modes[i] = modes[i].is<int>() ? modes[i] : CONSTANT.NO_VALUE_INT;
        }
    }
}

void PortState::copyDataInto(int* destination) {
    if (destination) {
        JsonArray data = holder[SCHEMA_STATE.DATA].as<JsonArray>();
        for (int i = 0; i < CONSTANT.PORT_COUNT; ++i) {
            destination[i] = data[i].as<int>();
        }
    }
}

JsonArrayConst PortState::getDataAsJson() {
    return holder[SCHEMA_STATE.DATA].as<JsonArrayConst>();
}

void PortState::setData(const int* data) {
    if (data) {
        eraseData();
        JsonArray _data = holder[SCHEMA_STATE.DATA].as<JsonArray>();
        for (int i = 0; i < CONSTANT.PORT_COUNT; ++i) {
            _data[i] = data[i];
        }
    }
}

void PortState::setData(JsonArrayConst data) {
    if (data) {
        eraseData();
        JsonArray _data = holder[SCHEMA_STATE.DATA].as<JsonArray>();
        for (int i = 0; i < CONSTANT.PORT_COUNT && i < data.size(); ++i) {
            _data[i] = data[i].is<int>() ? data[i] : CONSTANT.NO_VALUE_INT;
        }
    }
}

void PortState::setPortData(const int& port, int data) {
    if (port >= 0 && port < CONSTANT.PORT_COUNT) {
        JsonArray state = holder[SCHEMA_STATE.DATA].as<JsonArray>();
        state[port] = data;
    }
}

JsonObjectConst PortState::getAsJson() {
    return holder.as<JsonObjectConst>();
}
