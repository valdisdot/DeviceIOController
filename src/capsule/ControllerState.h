#ifndef CONTROLLER_STATE_H
#define CONTROLLER_STATE_H

#include "util/Constant.h"
#include "util/JsonSchema.h"
#include "util/Function.h"
#include <ArduinoJson.h>

class ControllerState {
   private:
    JsonDocument holder;

   public:
   ControllerState();
    void setMode(int mode);
    void setSignalStrength(int signalStrength);
    void setMemory(int memoryBytes);
    void setLastRebootReason(int rebootReason);
    int getMode();
    int getSignalStrenght();
    int getMemory();
    int getLastRebootReason();
    JsonObjectConst getAsJson();
};

#endif