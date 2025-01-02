#include "task/ControllerTasks.h"

PortHandlerStatefulCollectorTask::PortHandlerStatefulCollectorTask(PortHandler& portHandler)
    : Task(
          "stateful_collector_task",
          0,
          $TASK.TASK$PORT_HANDLER$STATEFUL_COLLECTOR$DELAY,
          $TASK.TYPE$CYCLIC,
          $TASK.TASK$PORT_HANDLER$STATEFUL_COLLECTOR$STACK_SIZE,
          $TASK.TASK$PORT_HANDLER$STATEFUL_COLLECTOR$PRIORITY),
      portHandler(portHandler) {}

void PortHandlerStatefulCollectorTask::execute() {
    portHandler.checkStatefulPorts();
}

BackupTask::BackupTask(InternalStorage& storage)
    : Task(
          "data_exchanger_saver_task",
          0,
          $TASK.TASK$INTERNAL_STORAGE$DELAY,
          $TASK.TYPE$CYCLIC,
          $TASK.TASK$INTERNAL_STORAGE$STACK_SIZE,
          $TASK.TASK$INTERNAL_STORAGE$PRIORITY),
      storage(storage) {}

void BackupTask::execute() {
    storage.backupConfiguration();
    storage.backupState();
}

ClientRunnerTask::ClientRunnerTask(BaseClient& client)
    : Task(
          "client_runner_task",
          0,
          $TASK.TASK$CLIENT_RUNNER$DELAY,
          $TASK.TYPE$CYCLIC,
          $TASK.TASK$CLIENT_RUNNER$STACK_SIZE,
          $TASK.TASK$CLIENT_RUNNER$PRIORITY),
      client(client) {}

void ClientRunnerTask::execute() {
    client.step();
}
