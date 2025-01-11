#ifndef CONNECTION_CONFIGURATION_H
#define CONNECTION_CONFIGURATION_H

#include "util/Constant.h"
#include "util/JsonSchema.h"
#include "util/Function.h"
#include <ArduinoJson.h>

class NetworkConfiguration {
   private:
    JsonDocument holder;

   public:
    int getMode();
    const char* getSSID();
    const char* getPassword();
    const char* getAPNName();
    const char* getAPNUser();
    const char* getAPNPassword();
    JsonObjectConst getAsJson();
    void updateFromJson(JsonObjectConst configuration);
};

#endif