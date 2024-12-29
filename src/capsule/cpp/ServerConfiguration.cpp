#include "capsule/ServerConfiguration.h"

const char* ServerConfiguration::getURL() {
    return holder[SCHEMA_SERVER_CONFIGURATION.ADDRESS].is<const char*>() ? holder[SCHEMA_SERVER_CONFIGURATION.ADDRESS].as<const char*>() : CONSTANT.NO_VALUE_STR;
}

int ServerConfiguration::getPort() {
    return holder[SCHEMA_SERVER_CONFIGURATION.PORT].is<int>() ? holder[SCHEMA_SERVER_CONFIGURATION.PORT].as<int>() : 0;
}

const char* ServerConfiguration::getUser() {
    return holder[SCHEMA_SERVER_CONFIGURATION.USER].is<const char*>() ? holder[SCHEMA_SERVER_CONFIGURATION.USER].as<const char*>() : CONSTANT.NO_VALUE_STR;
}

const char* ServerConfiguration::getPassword() {
    return holder[SCHEMA_SERVER_CONFIGURATION.PASSWORD].is<const char*>() ? holder[SCHEMA_SERVER_CONFIGURATION.PASSWORD].as<const char*>() : CONSTANT.NO_VALUE_STR;
}

bool ServerConfiguration::isSecure() {
    return holder[SCHEMA_SERVER_CONFIGURATION.SECURE].is<bool>() ? holder[SCHEMA_SERVER_CONFIGURATION.SECURE].as<bool>() : false;
}

const char* ServerConfiguration::getCertificate() {
    return holder[SCHEMA_SERVER_CONFIGURATION.CERTIFICATE].is<const char*>() ? holder[SCHEMA_SERVER_CONFIGURATION.CERTIFICATE].as<const char*>() : CONSTANT.NO_VALUE_STR;
}

JsonObjectConst ServerConfiguration::getAsJson() {
    return holder.as<JsonObject>();
}

void ServerConfiguration::updateFromJson(JsonObjectConst configuration) {
    if (configuration) {
        if (configuration[SCHEMA_SERVER_CONFIGURATION.ADDRESS].is<const char*>()) holder[SCHEMA_SERVER_CONFIGURATION.ADDRESS] = configuration[SCHEMA_SERVER_CONFIGURATION.ADDRESS];
        if (configuration[SCHEMA_SERVER_CONFIGURATION.PORT].is<int>()) holder[SCHEMA_SERVER_CONFIGURATION.PORT] = configuration[SCHEMA_SERVER_CONFIGURATION.PORT];
        if (configuration[SCHEMA_SERVER_CONFIGURATION.USER].is<const char*>()) holder[SCHEMA_SERVER_CONFIGURATION.USER] = configuration[SCHEMA_SERVER_CONFIGURATION.USER];
        if (configuration[SCHEMA_SERVER_CONFIGURATION.PASSWORD].is<const char*>()) holder[SCHEMA_SERVER_CONFIGURATION.PASSWORD] = configuration[SCHEMA_SERVER_CONFIGURATION.PASSWORD];
        if (configuration[SCHEMA_SERVER_CONFIGURATION.SECURE].is<bool>()) holder[SCHEMA_SERVER_CONFIGURATION.SECURE] = configuration[SCHEMA_SERVER_CONFIGURATION.SECURE];
        if (configuration[SCHEMA_SERVER_CONFIGURATION.CERTIFICATE].is<const char*>()) holder[SCHEMA_SERVER_CONFIGURATION.CERTIFICATE] = configuration[SCHEMA_SERVER_CONFIGURATION.CERTIFICATE];
    }
}
