/**
 * @file ControllerTasks.h
 * @brief Defines specialized tasks for handling port state collection and data saving operations.
 *
 * This header file provides concrete implementations of the `Task` class
 * for managing stateful port data collection and saving data to internal storage.
 */

#ifndef CONTROLLER_TASKS_H
#define CONTROLLER_TASKS_H

#include "client/BaseClient.h"
#include "port/PortHandler.h"
#include "storage/InternalStorage.h"
#include "task/Task.h"
#include "constant/TaskConstants.h"

/**
 * @class PortHandlerStatefulCollectorTask
 * @brief Collects stateful data from the port handler periodically.
 *
 * This task is configured as a cyclic task and runs at a predefined interval,
 * collecting stateful data using the provided `PortHandler` instance.
 */
class PortHandlerStatefulCollectorTask : public Task {
   private:
    PortHandler portHandler; /**< Reference to the port handler for data collection. */

   public:
    /**
     * @brief Constructs a `PortHandlerStatefulCollectorTask` object.
     * @param portHandler Reference to the `PortHandler` object used for data collection.
     * @param constants Reference to `TaskConstants` for configuration.
     */
    PortHandlerStatefulCollectorTask(const PortHandler& portHandler, const TaskConstants& constants);

    /**
     * @brief Executes the task to collect stateful data from the port handler.
     */
    void execute() override;
};

/**
 * @class DataExchangerSaverTask
 * @brief Saves data modes and states periodically to internal storage.
 *
 * This task is configured as a cyclic task and runs at a predefined interval,
 * saving data using the provided `InternalStorage` instance.
 */
class DataExchangerSaverTask : public Task {
   private:
    InternalStorage storage; /**< Reference to the internal storage for saving data. */

   public:
    /**
     * @brief Constructs a `DataExchangerSaverTask` object.
     * @param storage Reference to the `InternalStorage` object for saving data.
     * @param constants Reference to `TaskConstants` for configuration.
     */
    DataExchangerSaverTask(const InternalStorage& storage, const TaskConstants& constants);

    /**
     * @brief Executes the task to save modes and state to internal storage.
     */
    void execute() override;
};

class ClientRunnerTask : public Task {
   private:
    BaseClient& client;

   public:
    ClientRunnerTask(BaseClient& client, const TaskConstants& constants);

    void execute() override;
};

#endif
