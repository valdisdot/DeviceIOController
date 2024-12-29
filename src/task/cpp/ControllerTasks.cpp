#include "task/ControllerTasks.h"

PortHandlerStatefulCollectorTask::PortHandlerStatefulCollectorTask(PortHandler& portHandler)
    : Task(
          "stateful_collector_task",
          0,
          TASK_CONSTANT.PORT_HANDLER_STATEFUL_COLLECTOR_TASK_DELAY,
          TASK_CONSTANT.TASK_TYPE_CYCLIC,
          TASK_CONSTANT.PORT_HANDLER_STATEFUL_COLLECTOR_TASK_STACK_SIZE,
          TASK_CONSTANT.PORT_HANDLER_STATEFUL_COLLECTOR_TASK_PRIORITY),
      portHandler(portHandler) {}

void PortHandlerStatefulCollectorTask::execute() {
    portHandler.checkStatefulPorts();
}

BackupTask::BackupTask(InternalStorage& storage)
    : Task(
          "data_exchanger_saver_task",
          0,
          TASK_CONSTANT.INTERNAL_STORAGE_TASK_DELAY,
          TASK_CONSTANT.TASK_TYPE_CYCLIC,
          TASK_CONSTANT.INTERNAL_STORAGE_TASK_STACK_SIZE,
          TASK_CONSTANT.INTERNAL_STORAGE_TASK_PRIORITY),
      storage(storage) {}

void BackupTask::execute() {
    storage.backupConfiguration();
    storage.backupState();
}

ClientRunnerTask::ClientRunnerTask(BaseClient& client)
    : Task(
          "client_runner_task",
          0,
          TASK_CONSTANT.CLIENT_RUNNER_TASK_DELAY,
          TASK_CONSTANT.TASK_TYPE_CYCLIC,
          TASK_CONSTANT.CLIENT_RUNNER_TASK_STACK_SIZE,
          TASK_CONSTANT.CLIENT_RUNNER_TASK_PRIORITY),
      client(client) {}

void ClientRunnerTask::execute() {
    client.step();
}
