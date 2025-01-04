#ifndef CONTROLLER_STATE_H
#define CONTROLLER_STATE_H

#include "system/MicroSystem.h"

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