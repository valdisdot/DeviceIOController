#ifndef CONNECTION_CONFIGURATION_H
#define CONNECTION_CONFIGURATION_H

#include "system/MicroSystem.h"

class ConnectionConfiguration {
   private:
    JsonDocument holder;

   public:
    int getMode();
    const char* getSSID();
    const char* getPassword();
    const char* getAPNName();
    const char* getAPNUser();
    const char* getAPNPassword();
    int getTransmissionInterval();
    JsonObjectConst getAsJson();
    void updateFromJson(JsonObjectConst configuration);
};

#endif