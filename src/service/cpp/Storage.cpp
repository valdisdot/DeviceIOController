#include "service/Storage.h"

Storage::Storage(PortState& state, ControllerState& controllerState, NetworkConfiguration& connectionConfiguration, ServerConfiguration& serverConfiguration, ControllerConfiguration& controllerConfiguration)
    : state(state), controllerState(controllerState), connectionConfiguration(connectionConfiguration), serverConfiguration(serverConfiguration), controllerConfiguration(controllerConfiguration) {
}

void Storage::restoreConfiguration() {
    preferences.begin($INTERNAL_STORAGE.CONFIGURATION);
    JsonVariant object;
    if (preferences.isKey($INTERNAL_STORAGE.CONFIGURATION$NETWORK)) {
        preferences.getString($INTERNAL_STORAGE.CONFIGURATION$NETWORK, buffer, $SYSTEM.SIZE$1K);
        object = doc[$INTERNAL_STORAGE.CONFIGURATION$NETWORK].to<JsonVariant>();
        deserializeJson(object, buffer);
        connectionConfiguration.updateFromJson(object.as<JsonObjectConst>());
    }
    if (preferences.isKey($INTERNAL_STORAGE.CONFIGURATION$SERVER)) {
        preferences.getString($INTERNAL_STORAGE.CONFIGURATION$SERVER, buffer, $SYSTEM.SIZE$1K);
        object = doc[$INTERNAL_STORAGE.CONFIGURATION$SERVER].to<JsonVariant>();
        deserializeJson(object, buffer);
        serverConfiguration.updateFromJson(object.as<JsonObjectConst>());
    }
    if (preferences.isKey($INTERNAL_STORAGE.CONFIGURATION$CONTROLLER)) {
        preferences.getString($INTERNAL_STORAGE.CONFIGURATION$CONTROLLER, buffer, $SYSTEM.SIZE$1K);
        object = doc[$INTERNAL_STORAGE.CONFIGURATION$CONTROLLER].to<JsonVariant>();
        deserializeJson(object, buffer);
        controllerConfiguration.updateFromJson(object.as<JsonObjectConst>());
    }
    preferences.end();
}

void Storage::restoreState() {
    preferences.begin($INTERNAL_STORAGE.STATE);
    JsonVariant array;
    if (preferences.isKey($INTERNAL_STORAGE.STATE$MODES)) {
        preferences.getString($INTERNAL_STORAGE.STATE$MODES, buffer, $SYSTEM.SIZE$1K);
        array = doc[$INTERNAL_STORAGE.STATE$MODES].to<JsonVariant>();
        deserializeJson(array, buffer);
        state.setModes(array.as<JsonArrayConst>());
    }
    if (preferences.isKey($INTERNAL_STORAGE.STATE$DATA)) {
        preferences.getString($INTERNAL_STORAGE.STATE$DATA, buffer, $SYSTEM.SIZE$1K);
        array = doc[$INTERNAL_STORAGE.STATE$DATA].to<JsonVariant>();
        deserializeJson(array, buffer);
        state.setData(array.as<JsonArrayConst>());
    }
    preferences.end();
}

void Storage::backupConfiguration() {
    preferences.begin($INTERNAL_STORAGE.CONFIGURATION);
    serializeJson(connectionConfiguration.getAsJson(), buffer, $SYSTEM.SIZE$1K);
    preferences.putString($INTERNAL_STORAGE.CONFIGURATION$NETWORK, buffer);
    serializeJson(serverConfiguration.getAsJson(), buffer, $SYSTEM.SIZE$1K);
    preferences.putString($INTERNAL_STORAGE.CONFIGURATION$SERVER, buffer);
    serializeJson(controllerConfiguration.getAsJson(), buffer, $SYSTEM.SIZE$1K);
    preferences.putString($INTERNAL_STORAGE.CONFIGURATION$CONTROLLER, buffer);
    preferences.end();
}

void Storage::backupState() {
    preferences.begin($INTERNAL_STORAGE.STATE);
    serializeJson(state.getModesAsJson(), buffer, $SYSTEM.SIZE$1K);
    preferences.putString($INTERNAL_STORAGE.STATE$MODES, buffer);
    serializeJson(state.getDataAsJson(), buffer, $SYSTEM.SIZE$1K);
    preferences.putString($INTERNAL_STORAGE.STATE$DATA, buffer);
    preferences.end();
}

void Storage::erase() {
    preferences.begin($INTERNAL_STORAGE.STATE);
    preferences.clear();
    preferences.end();
    preferences.begin($INTERNAL_STORAGE.CONFIGURATION);
    preferences.clear();
    preferences.end();
}

PortState& Storage::getPortState() {
    return state;
}

ControllerState& Storage::getControllerState() {
    return controllerState;
}

NetworkConfiguration& Storage::getConnectionConfiguration() {
    return connectionConfiguration;
}

ServerConfiguration& Storage::getServerConfiguration() {
    return serverConfiguration;
}

ControllerConfiguration& Storage::getControllerConfiguration() {
    return controllerConfiguration;
}
