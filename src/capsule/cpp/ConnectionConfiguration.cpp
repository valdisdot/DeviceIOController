#include "capsule/ConnectionConfiguration.h"

int ConnectionConfiguration::getMode() {
    return holder[SCHEMA_CONNECTION_CONFIGURATION.MODE].is<int>() ? holder[SCHEMA_CONNECTION_CONFIGURATION.MODE].as<int>() : CONSTANT.CONNECTION_MODE_SERIAL;
}

const char* ConnectionConfiguration::getSSID() {
    return holder[SCHEMA_CONNECTION_CONFIGURATION.SSID].is<const char*>() ? holder[SCHEMA_CONNECTION_CONFIGURATION.MODE].as<const char*>() : CONSTANT.NO_VALUE_STR;
}

const char* ConnectionConfiguration::getPassword() {
    return holder[SCHEMA_CONNECTION_CONFIGURATION.PASSWORD].is<const char*>() ? holder[SCHEMA_CONNECTION_CONFIGURATION.PASSWORD].as<const char*>() : CONSTANT.NO_VALUE_STR;
}

const char* ConnectionConfiguration::getAPNName() {
    return holder[SCHEMA_CONNECTION_CONFIGURATION.APN_NAME].is<const char*>() ? holder[SCHEMA_CONNECTION_CONFIGURATION.APN_NAME].as<const char*>() : CONSTANT.NO_VALUE_STR;
}

const char* ConnectionConfiguration::getAPNUser() {
    return holder[SCHEMA_CONNECTION_CONFIGURATION.APN_USER].is<const char*>() ? holder[SCHEMA_CONNECTION_CONFIGURATION.APN_USER].as<const char*>() : CONSTANT.NO_VALUE_STR;
}

const char* ConnectionConfiguration::getAPNPassword() {
    return holder[SCHEMA_CONNECTION_CONFIGURATION.APN_PASSWORD].is<const char*>() ? holder[SCHEMA_CONNECTION_CONFIGURATION.APN_PASSWORD].as<const char*>() : CONSTANT.NO_VALUE_STR;
}

int ConnectionConfiguration::getTransmissionInterval() {
    return holder[SCHEMA_CONNECTION_CONFIGURATION.TRANSMISSION_INTERVAL].is<int>() ? holder[SCHEMA_CONNECTION_CONFIGURATION.TRANSMISSION_INTERVAL].as<int>() : 1000;
}

JsonObjectConst ConnectionConfiguration::getAsJson() {
    return holder.as<JsonObjectConst>();
}

void ConnectionConfiguration::updateFromJson(JsonObjectConst configuration) {
    if (configuration) {
        if (configuration[SCHEMA_CONNECTION_CONFIGURATION.MODE].is<int>()) {
            int mode = configuration[SCHEMA_CONNECTION_CONFIGURATION.MODE];
            if(mode < CONSTANT.CONNECTION_MODE_SERIAL || mode > CONSTANT.CONNECTION_MODE_SERIAL) mode = CONSTANT.CONNECTION_MODE_SERIAL;
            holder[SCHEMA_CONNECTION_CONFIGURATION.MODE] = mode;
        } else holder[SCHEMA_CONNECTION_CONFIGURATION.MODE] = CONSTANT.CONNECTION_MODE_SERIAL;
        if (configuration[SCHEMA_CONNECTION_CONFIGURATION.SSID].is<const char*>()) holder[SCHEMA_CONNECTION_CONFIGURATION.SSID] = configuration[SCHEMA_CONNECTION_CONFIGURATION.SSID];
        if (configuration[SCHEMA_CONNECTION_CONFIGURATION.PASSWORD].is<const char*>()) holder[SCHEMA_CONNECTION_CONFIGURATION.PASSWORD] = configuration[SCHEMA_CONNECTION_CONFIGURATION.PASSWORD];
        if (configuration[SCHEMA_CONNECTION_CONFIGURATION.APN_NAME].is<const char*>()) holder[SCHEMA_CONNECTION_CONFIGURATION.APN_NAME] = configuration[SCHEMA_CONNECTION_CONFIGURATION.APN_NAME];
        if (configuration[SCHEMA_CONNECTION_CONFIGURATION.APN_USER].is<const char*>()) holder[SCHEMA_CONNECTION_CONFIGURATION.APN_USER] = configuration[SCHEMA_CONNECTION_CONFIGURATION.APN_USER];
        if (configuration[SCHEMA_CONNECTION_CONFIGURATION.APN_PASSWORD].is<const char*>()) holder[SCHEMA_CONNECTION_CONFIGURATION.APN_PASSWORD] = configuration[SCHEMA_CONNECTION_CONFIGURATION.APN_PASSWORD];
        if (configuration[SCHEMA_CONNECTION_CONFIGURATION.TRANSMISSION_INTERVAL].is<int>()) holder[SCHEMA_CONNECTION_CONFIGURATION.TRANSMISSION_INTERVAL] = configuration[SCHEMA_CONNECTION_CONFIGURATION.TRANSMISSION_INTERVAL];
    }
}
