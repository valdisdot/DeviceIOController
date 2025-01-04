#include "capsule/ControllerState.h"

ControllerState::ControllerState() {
    holder[JSON$CONTROLLER_STATE.MODE] = $SYSTEM.NO_VALUE$INT;
    holder[JSON$CONTROLLER_STATE.SIGNAL_STRENGTH] = $SYSTEM.NO_VALUE$INT;
    holder[JSON$CONTROLLER_STATE.MEMORY] = $SYSTEM.NO_VALUE$INT;
    holder[JSON$CONTROLLER_STATE.REBOOT_REASON] = $SYSTEM.NO_VALUE$INT;
}

void ControllerState::setMode(int mode) {
    holder[JSON$CONTROLLER_STATE.MODE] = mode;
}

void ControllerState::setSignalStrength(int signalStrength) {
    holder[JSON$CONTROLLER_STATE.SIGNAL_STRENGTH] = signalStrength;
}

void ControllerState::setMemory(int memory) {
    holder[JSON$CONTROLLER_STATE.MEMORY] = memory;
}

void ControllerState::setLastRebootReason(int rebootReason) {
    holder[JSON$CONTROLLER_STATE.REBOOT_REASON] = rebootReason;
}

int ControllerState::getMode() {
    return holder[JSON$CONTROLLER_STATE.MODE].as<int>();
}

int ControllerState::getSignalStrenght() {
    return holder[JSON$CONTROLLER_STATE.SIGNAL_STRENGTH].as<int>();
}

int ControllerState::getMemory() {
    return holder[JSON$CONTROLLER_STATE.MEMORY].as<int>();
}

int ControllerState::getLastRebootReason() {
    return holder[JSON$CONTROLLER_STATE.REBOOT_REASON].as<int>();
}

JsonObjectConst ControllerState::getAsJson() {
    holder[JSON$MESSAGE.TIMESTAMP] = millis();
    return holder.as<JsonObjectConst>();
}
