#ifndef CONTROLLER_TASKS_H
#define CONTROLLER_TASKS_H

#include "system/MicroSystem.h"
#include "task/Task.h"
#include "client/BaseClient.h"
#include "service/PortHandler.h"
#include "service/InternalStorage.h"

class PortHandlerStatefulCollectorTask : public Task {
   private:
    PortHandler& portHandler; 

   public:
    PortHandlerStatefulCollectorTask(PortHandler& portHandler);
    void execute() override;
};

class BackupTask : public Task {
   private:
    InternalStorage& storage; 

   public:
    BackupTask(InternalStorage& storage);
    void execute() override;
};

class ClientRunnerTask : public Task {
   private:
    BaseClient& client;

   public:
    ClientRunnerTask(BaseClient& client);

    void execute() override;
};

#endif
