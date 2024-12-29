#ifndef CONTROLLER_HANDLER_H
#define CONTROLLER_HANDLER_H

#include "system/MicroSystem.h"
#include "capsule/ControllerState.h"

class ControllerHandler {
   private:
    ControllerState& state;
    char id[CONSTANT.SIZE_16];

   public:
    ControllerHandler(ControllerState& state);
    const char* getId();
    void pushControllerState();
    void reboot();
    ControllerState& getControllerState();
};

#endif
