#include "service/InternalStorage.h"

InternalStorage::InternalStorage(PortState& state, ConnectionConfiguration& connectionConfiguration, ServerConfiguration& serverConfiguration)
    : state(state), connectionConfiguration(connectionConfiguration), serverConfiguration(serverConfiguration) {
}

void InternalStorage::restoreConfiguration() {
    preferences.begin(SCHEMA_BASE.CONFIGURATION);
    JsonDocument doc;
    JsonVariant object;
    char buffer[CONSTANT.SIZE_1K];
    if (preferences.isKey(SCHEMA_CONNECTION_CONFIGURATION.ROOT)) {
        preferences.getString(SCHEMA_CONNECTION_CONFIGURATION.ROOT, buffer, CONSTANT.SIZE_1K);
        object = doc[SCHEMA_CONNECTION_CONFIGURATION.ROOT].to<JsonVariant>();
        deserializeJson(object, buffer);
        connectionConfiguration.updateFromJson(object.as<JsonObjectConst>());
    }
    if (preferences.isKey(SCHEMA_SERVER_CONFIGURATION.ROOT)) {
        preferences.getString(SCHEMA_SERVER_CONFIGURATION.ROOT, buffer, CONSTANT.SIZE_1K);
        object = doc[SCHEMA_SERVER_CONFIGURATION.ROOT].to<JsonVariant>();
        deserializeJson(object, buffer);
        serverConfiguration.updateFromJson(object.as<JsonObjectConst>());
    }
    preferences.end();
}

void InternalStorage::restoreState() {
    preferences.begin(SCHEMA_BASE.STATE);
    JsonDocument doc;
    JsonVariant array;
    char buffer[CONSTANT.SIZE_1K];
    if (preferences.isKey(SCHEMA_STATE.MODES)) {
        preferences.getString(SCHEMA_STATE.MODES, buffer, CONSTANT.SIZE_1K);
        array = doc[SCHEMA_STATE.MODES].to<JsonVariant>();
        deserializeJson(array, buffer);
        state.setModes(array.as<JsonArrayConst>());
    }
    if (preferences.isKey(SCHEMA_STATE.DATA)) {
        preferences.getString(SCHEMA_STATE.DATA, buffer, CONSTANT.SIZE_1K);
        array = doc[SCHEMA_STATE.DATA].to<JsonVariant>();
        deserializeJson(array, buffer);
        state.setData(array.as<JsonArrayConst>());
    }
    preferences.end();
}

void InternalStorage::backupConfiguration() {
    preferences.begin(SCHEMA_BASE.CONFIGURATION);
    char buffer[CONSTANT.SIZE_1K];
    serializeJson(connectionConfiguration.getAsJson(), buffer, CONSTANT.SIZE_1K);
    preferences.putString(SCHEMA_CONNECTION_CONFIGURATION.ROOT, buffer);
    serializeJson(serverConfiguration.getAsJson(), buffer, CONSTANT.SIZE_1K);
    preferences.putString(SCHEMA_SERVER_CONFIGURATION.ROOT, buffer);
    preferences.end();
}

void InternalStorage::backupState() {
    preferences.begin(SCHEMA_BASE.STATE);
    char buffer[CONSTANT.SIZE_1K];
    serializeJson(state.getModesAsJson(), buffer, CONSTANT.SIZE_1K);
    preferences.putString(SCHEMA_STATE.MODES, buffer);
    serializeJson(state.getDataAsJson(), buffer, CONSTANT.SIZE_1K);
    preferences.putString(SCHEMA_STATE.DATA, buffer);
    preferences.end();
}

void InternalStorage::erase() {
    preferences.begin(SCHEMA_BASE.STATE);
    preferences.clear();
    preferences.end();
    preferences.begin(SCHEMA_BASE.CONFIGURATION);
    preferences.clear();
    preferences.end();
}

PortState& InternalStorage::getPortState() {
    return state;
}

ConnectionConfiguration& InternalStorage::getConnectionConfiguration() {
    return connectionConfiguration;
}

ServerConfiguration& InternalStorage::getServerConfiguration() {
    return serverConfiguration;
}
