#include "task/ControllerTasks.h"

PortHandlerStatefulCollectorTask::PortHandlerStatefulCollectorTask(const PortHandler& portHandler, const TaskConstants& constants)
    : Task(
          "stateful_collector_task",
          0,
          constants.PORT_HANDLER_STATEFUL_COLLECTOR_TASK_DELAY,
          constants.TASK_TYPE_CYCLIC,
          constants.PORT_HANDLER_STATEFUL_COLLECTOR_TASK_STACK_SIZE,
          constants.PORT_HANDLER_STATEFUL_COLLECTOR_TASK_PRIORITY,
          constants),
      portHandler(portHandler) {}

void PortHandlerStatefulCollectorTask::execute() {
    portHandler.collectStatefulData();
}

DataExchangerSaverTask::DataExchangerSaverTask(const InternalStorage& storage, const TaskConstants& constants)
    : Task(
          "data_exchanger_saver_task",
          0,
          constants.INTERNAL_STORAGE_TASK_DELAY,
          constants.TASK_TYPE_CYCLIC,
          constants.INTERNAL_STORAGE_TASK_STACK_SIZE,
          constants.INTERNAL_STORAGE_TASK_PRIORITY,
          constants),
      storage(storage) {}

void DataExchangerSaverTask::execute() {
    storage.saveModes();
    storage.saveState();
}

ClientRunnerTask::ClientRunnerTask(BaseClient& client, const TaskConstants& constants)
    : Task(
          "client_runner_task",
          0,
          constants.CLIENT_RUNNER_TASK_DELAY,
          constants.TASK_TYPE_CYCLIC,
          constants.CLIENT_RUNNER_TASK_STACK_SIZE,
          constants.CLIENT_RUNNER_TASK_PRIORITY,
          constants),
      client(client) {}

void ClientRunnerTask::execute() {
    client.step();
}
