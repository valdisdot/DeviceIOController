#include "capsule/NetworkConfiguration.h"

int NetworkConfiguration::getMode() {
    return holder[JSON$NETWORK_CONFIGURATION.MODE].is<int>() ? holder[JSON$NETWORK_CONFIGURATION.MODE].as<int>() : $NETWORK.MODE$SERIAL;
}

const char* NetworkConfiguration::getSSID() {
    return holder[JSON$NETWORK_CONFIGURATION.SSID].is<const char*>() ? holder[JSON$NETWORK_CONFIGURATION.SSID].as<const char*>() : $SYSTEM.NO_VALUE$STR;
}

const char* NetworkConfiguration::getPassword() {
    return holder[JSON$NETWORK_CONFIGURATION.PASSWORD].is<const char*>() ? holder[JSON$NETWORK_CONFIGURATION.PASSWORD].as<const char*>() : $SYSTEM.NO_VALUE$STR;
}

const char* NetworkConfiguration::getAPNName() {
    return holder[JSON$NETWORK_CONFIGURATION.APN_NAME].is<const char*>() ? holder[JSON$NETWORK_CONFIGURATION.APN_NAME].as<const char*>() : $SYSTEM.NO_VALUE$STR;
}

const char* NetworkConfiguration::getAPNUser() {
    return holder[JSON$NETWORK_CONFIGURATION.APN_USER].is<const char*>() ? holder[JSON$NETWORK_CONFIGURATION.APN_USER].as<const char*>() : $SYSTEM.NO_VALUE$STR;
}

const char* NetworkConfiguration::getAPNPassword() {
    return holder[JSON$NETWORK_CONFIGURATION.APN_PASSWORD].is<const char*>() ? holder[JSON$NETWORK_CONFIGURATION.APN_PASSWORD].as<const char*>() : $SYSTEM.NO_VALUE$STR;
}

JsonObjectConst NetworkConfiguration::getAsJson() {
    return holder.as<JsonObjectConst>();
}

void NetworkConfiguration::updateFromJson(JsonObjectConst configuration) {
    if (configuration) {
        if (configuration[JSON$NETWORK_CONFIGURATION.MODE].is<int>()) {
            int mode = configuration[JSON$NETWORK_CONFIGURATION.MODE];
            if(mode < $NETWORK.MODE$SERIAL || mode > $NETWORK.MODE$CELLULAR) mode = $NETWORK.MODE$SERIAL;
            holder[JSON$NETWORK_CONFIGURATION.MODE] = mode;
        } else holder[JSON$NETWORK_CONFIGURATION.MODE] = $NETWORK.MODE$SERIAL;
        if (configuration[JSON$NETWORK_CONFIGURATION.SSID].is<const char*>()) holder[JSON$NETWORK_CONFIGURATION.SSID] = configuration[JSON$NETWORK_CONFIGURATION.SSID];
        if (configuration[JSON$NETWORK_CONFIGURATION.PASSWORD].is<const char*>()) holder[JSON$NETWORK_CONFIGURATION.PASSWORD] = configuration[JSON$NETWORK_CONFIGURATION.PASSWORD];
        if (configuration[JSON$NETWORK_CONFIGURATION.APN_NAME].is<const char*>()) holder[JSON$NETWORK_CONFIGURATION.APN_NAME] = configuration[JSON$NETWORK_CONFIGURATION.APN_NAME];
        if (configuration[JSON$NETWORK_CONFIGURATION.APN_USER].is<const char*>()) holder[JSON$NETWORK_CONFIGURATION.APN_USER] = configuration[JSON$NETWORK_CONFIGURATION.APN_USER];
        if (configuration[JSON$NETWORK_CONFIGURATION.APN_PASSWORD].is<const char*>()) holder[JSON$NETWORK_CONFIGURATION.APN_PASSWORD] = configuration[JSON$NETWORK_CONFIGURATION.APN_PASSWORD];
    }
}
