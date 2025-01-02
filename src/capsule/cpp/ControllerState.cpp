#include "capsule/ControllerState.h"

ControllerState::ControllerState() {
    holder[JSON$CONTROLLER_STATE.STATE].to<JsonObject>()[JSON$CONTROLLER_STATE.STATE$WIFI] = false;
    holder[JSON$CONTROLLER_STATE.STATE].as<JsonObject>()[JSON$CONTROLLER_STATE.STATE$CELLULAR] = false;
    holder[JSON$CONTROLLER_STATE.STATE].as<JsonObject>()[JSON$CONTROLLER_STATE.STATE$SERIAL] = false;
    holder[JSON$CONTROLLER_STATE.MEMORY] = $SYSTEM.NO_VALUE$INT;
    holder[JSON$CONTROLLER_STATE.REBOOT_REASON] = $SYSTEM.NO_VALUE$STR;
}

void ControllerState::setWiFiState(bool state) {
    holder[JSON$CONTROLLER_STATE.STATE].as<JsonObject>()[JSON$CONTROLLER_STATE.STATE$WIFI] = state;
}

void ControllerState::setCellularState(bool state) {
    holder[JSON$CONTROLLER_STATE.STATE].as<JsonObject>()[JSON$CONTROLLER_STATE.STATE$CELLULAR] = state;
}

void ControllerState::setSerialState(bool state) {
    holder[JSON$CONTROLLER_STATE.STATE].as<JsonObject>()[JSON$CONTROLLER_STATE.STATE$SERIAL] = state;
}

void ControllerState::setMemory(int state) {
    holder[JSON$CONTROLLER_STATE.MEMORY] = state;
}

void ControllerState::setLastRebootReason(const char* reason) {
    holder[JSON$CONTROLLER_STATE.REBOOT_REASON] = reason;
}

bool ControllerState::getWiFiState() {
    return holder[JSON$CONTROLLER_STATE.STATE].as<JsonObject>()[JSON$CONTROLLER_STATE.STATE$WIFI].as<bool>();
}

bool ControllerState::getCellularState() {
    return holder[JSON$CONTROLLER_STATE.STATE].as<JsonObject>()[JSON$CONTROLLER_STATE.STATE$CELLULAR].as<bool>();
}

bool ControllerState::getSerialState() {
    return holder[JSON$CONTROLLER_STATE.STATE].as<JsonObject>()[JSON$CONTROLLER_STATE.STATE$SERIAL].as<bool>();
}

int ControllerState::getMemory() {
    return holder[JSON$CONTROLLER_STATE.MEMORY].as<int>();
}

const char* ControllerState::getLastRebootReason() {
    return holder[JSON$CONTROLLER_STATE.REBOOT_REASON].as<const char*>();
}

JsonObjectConst ControllerState::getAsJson() {
    holder[JSON$MESSAGE.TIMESTAMP] = millis();
    return holder.as<JsonObjectConst>();
}
