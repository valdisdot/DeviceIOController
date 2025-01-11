#ifndef CONTROLLER_CONFIGURATION_H
#define CONTROLLER_CONFIGURATION_H

#include "util/Constant.h"
#include "util/JsonSchema.h"
#include "util/Function.h"
#include <ArduinoJson.h>

class ControllerConfiguration {
   private:
    JsonDocument holder;

   public:
    LogLevel getLogLevel();
    int getTransmissionInterval();
    JsonObjectConst getAsJson();
    void updateFromJson(JsonObjectConst configuration);
};

#endif