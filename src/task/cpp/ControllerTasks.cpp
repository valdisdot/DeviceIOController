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

BackupTask::BackupTask(Storage& storage)
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
