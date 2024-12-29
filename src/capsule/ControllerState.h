#ifndef CONTROLLER_STATE_H
#define CONTROLLER_STATE_H

#include "system/MicroSystem.h"

class ControllerState {
   private:
    JsonDocument holder;

   public:
   ControllerState();
    void setWiFiState(bool state);
    void setCellularState(bool state);
    void setSerialState(bool state);
    void setMaxMemoryState(int state);
    void setMinMemoryState(int state);
    void setLastRebootReason(const char *reason);
    bool getWiFiState();
    bool getCellularState();
    bool getSerialState();
    int getMaxMemoryState();
    int getMinMemoryState();
    const char* getLastRebootReason();
    JsonObjectConst getAsJson();
};

#endif