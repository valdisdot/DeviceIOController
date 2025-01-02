#ifndef CONTROLLER_CONFIGURATION_H
#define CONTROLLER_CONFIGURATION_H

#include "system/MicroSystem.h"

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