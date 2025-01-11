#ifndef INTERNAL_STORAGE_H
#define INTERNAL_STORAGE_H

#include <Preferences.h>
#include "util/Constant.h"
#include "util/JsonSchema.h"
#include "util/Function.h"
#include <ArduinoJson.h>
#include "capsule/PortState.h"
#include "capsule/ControllerState.h"
#include "capsule/NetworkConfiguration.h"
#include "capsule/ServerConfiguration.h"
#include "capsule/ControllerConfiguration.h"

class Storage {
   private:
    Preferences preferences;  
    PortState& state;
    ControllerState& controllerState;
    NetworkConfiguration& connectionConfiguration;
    ServerConfiguration& serverConfiguration;
    ControllerConfiguration& controllerConfiguration;

    JsonDocument doc;
    char buffer[$SYSTEM.SIZE$2K];

   public:
    Storage(PortState& state, ControllerState& controllerState, NetworkConfiguration& connectionConfiguration, ServerConfiguration& serverConfiguration, ControllerConfiguration& controllerConfiguration);
    void restoreConfiguration();
    void restoreState();
    void backupConfiguration();
    void backupState();
    void erase();
    PortState& getPortState();
    ControllerState& getControllerState();
    NetworkConfiguration& getConnectionConfiguration();
    ServerConfiguration& getServerConfiguration();
    ControllerConfiguration& getControllerConfiguration();
};

#endif
