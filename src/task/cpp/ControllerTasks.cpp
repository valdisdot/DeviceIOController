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
          $TASK.TASK$STORAGE_BACKUP$DELAY,
          $TASK.TYPE$CYCLIC,
          $TASK.TASK$STORAGE_BACKUP$STACK_SIZE,
          $TASK.TASK$STORAGE_BACKUP$PRIORITY),
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

MemoryCollector::MemoryCollector(ControllerState& controllerState)
    : Task(
          "memory_collector",
          0,
          $TASK.TASK$MEMORY_COLLECTOR$DELAY,
          $TASK.TYPE$CYCLIC,
          $TASK.TASK$MEMORY_COLLECTOR$STACK_SIZE,
          $TASK.TASK$MEMORY_COLLECTOR$PRIORITY),
      controllerState(controllerState) {}

void MemoryCollector::execute() {
    controllerState.setMemory(esp_get_free_heap_size());
}

WiFiSignalStrengthCollector::WiFiSignalStrengthCollector(ControllerState& controllerState) 
    : Task(
          "signal_strength_collector",
          0,
          $TASK.TASK$SIGNAL_STRENGTH_COLLECTOR$DELAY,
          $TASK.TYPE$CYCLIC,
          $TASK.TASK$SIGNAL_STRENGTH_COLLECTOR$STACK_SIZE,
          $TASK.TASK$SIGNAL_STRENGTH_COLLECTOR$PRIORITY),
      controllerState(controllerState) {}

void WiFiSignalStrengthCollector::execute() {
    controllerState.setSignalStrength(WiFi.RSSI());
}
