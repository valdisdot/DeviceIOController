#ifndef CONTROLLER_TASKS_H
#define CONTROLLER_TASKS_H

#include "util/Constant.h"
#include "util/JsonSchema.h"
#include "util/Function.h"
#include "task/Task.h"
#include "controller/MessageExchanger.h"
#include "service/PortHandler.h"
#include "service/Storage.h"
#include <WiFi.h>

class PortHandlerStatefulCollectorTask : public Task {
   private:
    PortHandler& portHandler; 

   public:
    PortHandlerStatefulCollectorTask(PortHandler& portHandler);
    void execute() override;
};

class BackupTask : public Task {
   private:
    Storage& storage; 

   public:
    BackupTask(Storage& storage);
    void execute() override;
};

class WiFiSignalStrengthCollector : public Task {
    private:
    ControllerState& controllerState;

    public:
    WiFiSignalStrengthCollector(ControllerState& controllerState);

    void execute() override;  
};

#endif
