#include "capsule/PortState.h"

PortState::PortState() {
    holder[JSON$STATE.MODES].to<JsonArray>();
    holder[JSON$STATE.DATA].to<JsonArray>();
}

void PortState::copyModesInto(int* destination) {
    if (destination) {
        JsonArray modes = holder[JSON$STATE.MODES].as<JsonArray>();
        for (int i = 0; i < $PORT.COUNT; ++i) {
            destination[i] = modes[i].as<int>();
        }
    }
}

JsonArrayConst PortState::getModesAsJson() {
    return holder[JSON$STATE.MODES].as<JsonArrayConst>();
}

void PortState::setModes(const int* modes) {
    if (modes) {
        JsonArray _modes = holder[JSON$STATE.MODES].as<JsonArray>();
        for (int i = 0; i < $PORT.COUNT; ++i) {
            _modes[i] = modes[i];
        }
    }
}

void PortState::setModes(JsonArrayConst modes) {
    if (modes) {
        JsonArray _modes = holder[JSON$STATE.MODES].as<JsonArray>();
        for (int i = 0; i < $PORT.COUNT && i < modes.size(); ++i) {
            _modes[i] = modes[i].is<int>() ? modes[i] : $SYSTEM.NO_VALUE$INT;
        }
    }
}

void PortState::setPortMode(const int& port, int mode) {
    if (port >= 0 && port < $PORT.COUNT) {
        JsonArray modes = holder[JSON$STATE.MODES].as<JsonArray>();
        modes[port] = mode;
    }
}

void PortState::copyDataInto(int* destination) {
    if (destination) {
        JsonArray data = holder[JSON$STATE.DATA].as<JsonArray>();
        for (int i = 0; i < $PORT.COUNT; ++i) {
            destination[i] = data[i].as<int>();
        }
    }
}

JsonArrayConst PortState::getDataAsJson() {
    return holder[JSON$STATE.DATA].as<JsonArrayConst>();
}

void PortState::setData(const int* data) {
    if (data) {
        JsonArray _data = holder[JSON$STATE.DATA].as<JsonArray>();
        for (int i = 0; i < $PORT.COUNT; ++i) {
            _data[i] = data[i];
        }
    }
}

void PortState::setData(JsonArrayConst data) {
    if (data) {
        JsonArray _data = holder[JSON$STATE.DATA].as<JsonArray>();
        for (int i = 0; i < $PORT.COUNT && i < data.size(); ++i) {
            _data[i] = data[i].is<int>() ? data[i] : $SYSTEM.NO_VALUE$INT;
        }
    }
}

void PortState::setPortData(const int& port, int data) {
    if (port >= 0 && port < $PORT.COUNT) {
        JsonArray state = holder[JSON$STATE.DATA].as<JsonArray>();
        state[port] = data;
    }
}

JsonObjectConst PortState::getAsJson() {
    holder[JSON$MESSAGE.TIMESTAMP] = millis();
    return holder.as<JsonObjectConst>();
}
