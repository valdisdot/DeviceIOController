#include "capsule/ControllerState.h"

ControllerState::ControllerState() {
    holder[SCHEMA_CONTROLLER_STATE.STATE].to<JsonObject>()[SCHEMA_CONTROLLER_STATE.STATE$WIFI] = false;
    holder[SCHEMA_CONTROLLER_STATE.STATE].to<JsonObject>()[SCHEMA_CONTROLLER_STATE.STATE$CELLULAR] = false;
    holder[SCHEMA_CONTROLLER_STATE.STATE].to<JsonObject>()[SCHEMA_CONTROLLER_STATE.STATE$SERIAL] = false;
    holder[SCHEMA_CONTROLLER_STATE.MEMORY].to<JsonObject>()[SCHEMA_CONTROLLER_STATE.MEMORY$MIN] = CONSTANT.NO_VALUE_INT;
    holder[SCHEMA_CONTROLLER_STATE.MEMORY].to<JsonObject>()[SCHEMA_CONTROLLER_STATE.MEMORY$MAX] = CONSTANT.NO_VALUE_INT;
    holder[SCHEMA_CONTROLLER_STATE.REBOOT_REASON] = CONSTANT.NO_VALUE_STR;
}

void ControllerState::setWiFiState(bool state) {
    holder[SCHEMA_CONTROLLER_STATE.STATE].as<JsonObject>()[SCHEMA_CONTROLLER_STATE.STATE$WIFI] = state;
}

void ControllerState::setCellularState(bool state) {
    holder[SCHEMA_CONTROLLER_STATE.STATE].as<JsonObject>()[SCHEMA_CONTROLLER_STATE.STATE$CELLULAR] = state;
}

void ControllerState::setSerialState(bool state) {
    holder[SCHEMA_CONTROLLER_STATE.STATE].as<JsonObject>()[SCHEMA_CONTROLLER_STATE.STATE$SERIAL] = state;
}

void ControllerState::setMaxMemoryState(int state) {
    holder[SCHEMA_CONTROLLER_STATE.MEMORY].as<JsonObject>()[SCHEMA_CONTROLLER_STATE.MEMORY$MIN] = state;
}

void ControllerState::setMinMemoryState(int state) {
    holder[SCHEMA_CONTROLLER_STATE.MEMORY].as<JsonObject>()[SCHEMA_CONTROLLER_STATE.MEMORY$MAX] = state;
}

void ControllerState::setLastRebootReason(const char* reason) {
    holder[SCHEMA_CONTROLLER_STATE.REBOOT_REASON] = reason;
}

bool ControllerState::getWiFiState() {
    return holder[SCHEMA_CONTROLLER_STATE.STATE].as<JsonObject>()[SCHEMA_CONTROLLER_STATE.STATE$WIFI].as<bool>();
}

bool ControllerState::getCellularState() {
    return holder[SCHEMA_CONTROLLER_STATE.STATE].as<JsonObject>()[SCHEMA_CONTROLLER_STATE.STATE$CELLULAR].as<bool>();
}

bool ControllerState::getSerialState() {
    return holder[SCHEMA_CONTROLLER_STATE.STATE].as<JsonObject>()[SCHEMA_CONTROLLER_STATE.STATE$SERIAL].as<bool>();
}

int ControllerState::getMaxMemoryState() {
    return holder[SCHEMA_CONTROLLER_STATE.MEMORY].as<JsonObject>()[SCHEMA_CONTROLLER_STATE.MEMORY$MIN].as<int>();
}

int ControllerState::getMinMemoryState() {
    return holder[SCHEMA_CONTROLLER_STATE.MEMORY].as<JsonObject>()[SCHEMA_CONTROLLER_STATE.MEMORY$MAX].as<int>();
}

const char* ControllerState::getLastRebootReason() {
    return holder[SCHEMA_CONTROLLER_STATE.REBOOT_REASON].as<const char*>();
}

JsonObjectConst ControllerState::getAsJson() {
    return holder.as<JsonObjectConst>();
}
