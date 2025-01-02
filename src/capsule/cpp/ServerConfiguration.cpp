#include "capsule/ServerConfiguration.h"

const char* ServerConfiguration::getURL() {
    return holder[JSON$SERVER_CONFIGURATION.ADDRESS].is<const char*>() ? holder[JSON$SERVER_CONFIGURATION.ADDRESS].as<const char*>() : $SYSTEM.NO_VALUE$STR;
}

int ServerConfiguration::getPort() {
    return holder[JSON$SERVER_CONFIGURATION.PORT].is<int>() ? holder[JSON$SERVER_CONFIGURATION.PORT].as<int>() : 0;
}

const char* ServerConfiguration::getUser() {
    return holder[JSON$SERVER_CONFIGURATION.USER].is<const char*>() ? holder[JSON$SERVER_CONFIGURATION.USER].as<const char*>() : $SYSTEM.NO_VALUE$STR;
}

const char* ServerConfiguration::getPassword() {
    return holder[JSON$SERVER_CONFIGURATION.PASSWORD].is<const char*>() ? holder[JSON$SERVER_CONFIGURATION.PASSWORD].as<const char*>() : $SYSTEM.NO_VALUE$STR;
}

bool ServerConfiguration::isSecure() {
    return holder[JSON$SERVER_CONFIGURATION.CERTIFICATE].is<const char*>() && !isBlank(holder[JSON$SERVER_CONFIGURATION.CERTIFICATE].as<const char*>());
}

const char* ServerConfiguration::getCertificate() {
    return holder[JSON$SERVER_CONFIGURATION.CERTIFICATE].is<const char*>() ? holder[JSON$SERVER_CONFIGURATION.CERTIFICATE].as<const char*>() : $SYSTEM.NO_VALUE$STR;
}

JsonObjectConst ServerConfiguration::getAsJson() {
    return holder.as<JsonObject>();
}

void ServerConfiguration::updateFromJson(JsonObjectConst configuration) {
    if (configuration) {
        if (configuration[JSON$SERVER_CONFIGURATION.ADDRESS].is<const char*>()) holder[JSON$SERVER_CONFIGURATION.ADDRESS] = configuration[JSON$SERVER_CONFIGURATION.ADDRESS];
        if (configuration[JSON$SERVER_CONFIGURATION.PORT].is<int>()) holder[JSON$SERVER_CONFIGURATION.PORT] = configuration[JSON$SERVER_CONFIGURATION.PORT];
        if (configuration[JSON$SERVER_CONFIGURATION.USER].is<const char*>()) holder[JSON$SERVER_CONFIGURATION.USER] = configuration[JSON$SERVER_CONFIGURATION.USER];
        if (configuration[JSON$SERVER_CONFIGURATION.PASSWORD].is<const char*>()) holder[JSON$SERVER_CONFIGURATION.PASSWORD] = configuration[JSON$SERVER_CONFIGURATION.PASSWORD];
        if (configuration[JSON$SERVER_CONFIGURATION.CERTIFICATE].is<const char*>()) holder[JSON$SERVER_CONFIGURATION.CERTIFICATE] = configuration[JSON$SERVER_CONFIGURATION.CERTIFICATE];
    }
}
