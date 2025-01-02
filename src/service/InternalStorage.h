#ifndef INTERNAL_STORAGE_H
#define INTERNAL_STORAGE_H

#include <Preferences.h>
#include "system/MicroSystem.h"
#include "capsule/PortState.h"
#include "capsule/NetworkConfiguration.h"
#include "capsule/ServerConfiguration.h"
#include "capsule/ControllerConfiguration.h"

class InternalStorage {
   private:
    Preferences preferences;  
    PortState& state;
    NetworkConfiguration& connectionConfiguration;
    ServerConfiguration& serverConfiguration;
    ControllerConfiguration& controllerConfiguration;

    JsonDocument doc;
    char buffer[$SYSTEM.SIZE$2K];

   public:
    InternalStorage(PortState& state, NetworkConfiguration& connectionConfiguration, ServerConfiguration& serverConfiguration, ControllerConfiguration& controllerConfiguration);
    void restoreConfiguration();
    void restoreState();
    void backupConfiguration();
    void backupState();
    void erase();
    PortState& getPortState();
    NetworkConfiguration& getConnectionConfiguration();
    ServerConfiguration& getServerConfiguration();
    ControllerConfiguration& getControllerConfiguration();
};

#endif
