#ifndef INTERNAL_STORAGE_H
#define INTERNAL_STORAGE_H

#include <Preferences.h>
#include "system/MicroSystem.h"
#include "capsule/PortState.h"
#include "capsule/ConnectionConfiguration.h"
#include "capsule/ServerConfiguration.h"

class InternalStorage {
   private:
    Preferences preferences;  
    PortState& state;
    ConnectionConfiguration& connectionConfiguration;
    ServerConfiguration& serverConfiguration;

   public:
    InternalStorage(PortState& state, ConnectionConfiguration& connectionConfiguration, ServerConfiguration& serverConfiguration);
    void restoreConfiguration();
    void restoreState();
    void backupConfiguration();
    void backupState();
    void erase();
    PortState& getPortState();
    ConnectionConfiguration& getConnectionConfiguration();
    ServerConfiguration& getServerConfiguration();
};

#endif
