#include "storage/InternalStorage.h"

InternalStorage::InternalStorage(JsonDocument *dataExchangeJson, const JsonSchema &jsonSchema, const ControllerConstants &constants)
    : dataExchangeJson(dataExchangeJson), jsonSchema(jsonSchema), constants(constants) {}

void InternalStorage::readAll() {
    readConfiguration();
    readModes();
    readState();
}

void InternalStorage::readConfiguration() {
    preferences.begin(jsonSchema.CONFIG_WORD);
    JsonObject config = (*dataExchangeJson)[jsonSchema.CONFIG_WORD].to<JsonObject>();
    if (preferences.isKey(jsonSchema.MODE_WORD)) config[jsonSchema.MODE_WORD] = preferences.getInt(jsonSchema.MODE_WORD, 0);
    char buffer[64];
    if (preferences.isKey(jsonSchema.SSID_WORD)) {
        preferences.getString(jsonSchema.SSID_WORD, buffer, 64);
        config[jsonSchema.SSID_WORD] = buffer;
    }
    if (preferences.isKey(jsonSchema.PASSWORD_WORD)) {
        preferences.getString(jsonSchema.PASSWORD_WORD, buffer, 64);
        config[jsonSchema.PASSWORD_WORD] = buffer;
    }
    if (preferences.isKey(jsonSchema.TRANSMISSION_INTERVAL_WORD)) config[jsonSchema.TRANSMISSION_INTERVAL_WORD] = preferences.getInt(jsonSchema.TRANSMISSION_INTERVAL_WORD, 3000);
    preferences.end();
}

void InternalStorage::readModes() {
    preferences.begin(jsonSchema.MODES_WORD);
    JsonObject modes = (*dataExchangeJson)[jsonSchema.MODES_WORD].to<JsonObject>();
    char port[16];
    for (int i = 1; i <= constants.LAST_PORT; ++i) {
        snprintf(port, 16, "%s%d", jsonSchema.PORT_PREFIX, i);
        if (preferences.isKey(port))
            modes[port] = preferences.getInt(port, 0);
    }
    preferences.end();
}

void InternalStorage::readState() {
    preferences.begin(jsonSchema.STATE_WORD);
    JsonObject state = (*dataExchangeJson)[jsonSchema.STATE_WORD].to<JsonObject>();
    char port[16];
    for (int i = 1; i <= constants.LAST_PORT; ++i) {
        snprintf(port, 16, "%s%d", jsonSchema.PORT_PREFIX, i);
        if (preferences.isKey(port))
            state[port] = preferences.getInt(port, 0);
    }
    preferences.end();
}

void InternalStorage::saveAll() {
    saveConfiguration();
    saveModes();
    saveState();
}

void InternalStorage::saveConfiguration() {
    if ((*dataExchangeJson)[jsonSchema.CONFIG_WORD].is<JsonObject>()) {
        JsonObject config = (*dataExchangeJson)[jsonSchema.CONFIG_WORD].as<JsonObject>();
        preferences.begin(jsonSchema.CONFIG_WORD);
        if (config[jsonSchema.MODE_WORD].is<signed int>())
            preferences.putInt(jsonSchema.MODE_WORD, config[jsonSchema.MODE_WORD].as<signed int>());
        if (config[jsonSchema.SSID_WORD].is<const char *>())
            preferences.putString(jsonSchema.SSID_WORD, config[jsonSchema.SSID_WORD].as<const char *>());
        if (config[jsonSchema.PASSWORD_WORD].is<const char *>())
            preferences.putString(jsonSchema.PASSWORD_WORD, config[jsonSchema.PASSWORD_WORD].as<const char *>());
        if (config[jsonSchema.TRANSMISSION_INTERVAL_WORD].is<signed int>())
            preferences.putInt(jsonSchema.TRANSMISSION_INTERVAL_WORD, config[jsonSchema.TRANSMISSION_INTERVAL_WORD].as<signed int>());
        preferences.end();
    }
}

void InternalStorage::saveModes() {
    if ((*dataExchangeJson)[jsonSchema.MODES_WORD].is<JsonObject>()) {
        JsonObject modes = (*dataExchangeJson)[jsonSchema.MODES_WORD].as<JsonObject>();
        preferences.begin(jsonSchema.MODES_WORD);
        char port[16];
        for (int i = 1; i <= constants.LAST_PORT; ++i) {
            snprintf(port, 16, "%s%d", jsonSchema.PORT_PREFIX, i);
            if (modes[port].is<signed int>())
                preferences.putInt(port, modes[port].as<signed int>());
        }
        preferences.end();
    }
}

void InternalStorage::saveState() {
    if ((*dataExchangeJson)[jsonSchema.STATE_WORD].is<JsonObject>()) {
        JsonObject state = (*dataExchangeJson)[jsonSchema.STATE_WORD].as<JsonObject>();
        preferences.begin(jsonSchema.STATE_WORD);
        char port[16];
        for (int i = 1; i <= constants.LAST_PORT; ++i) {
            snprintf(port, 16, "%s%d", jsonSchema.PORT_PREFIX, i);
            if (state[port].is<signed int>())
                preferences.putInt(port, state[port].as<signed int>());
        }
        preferences.end();
    }
}

void InternalStorage::erase() {
    preferences.begin(jsonSchema.CONFIG_WORD);
    preferences.clear();
    preferences.end();
    preferences.begin(jsonSchema.MODES_WORD);
    preferences.clear();
    preferences.end();
    preferences.begin(jsonSchema.STATE_WORD);
    preferences.clear();
    preferences.end();
}
