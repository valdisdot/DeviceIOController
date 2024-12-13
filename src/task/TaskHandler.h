/**
 * @file TaskHandler.h
 * @brief Provides an abstraction layer for managing tasks, encapsulating FreeRTOS logic.
 *
 * The `TaskHandler` class serves as a facade for task creation, suspension, resumption,
 * and state management, while abstracting the underlying FreeRTOS API.
 */

#ifndef TASK_HANDLER_H
#define TASK_HANDLER_H

#include <atomic>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "task/Task.h"
#include "constant/TaskConstants.h"

/**
 * @class TaskHandler
 * @brief Manages tasks and provides a high-level interface for task operations.
 *
 * The `TaskHandler` class handles task creation, scheduling, and state management.
 * It includes garbage collection logic to clean up deleted tasks and supports
 * task prioritization, suspension, and resumption.
 */
class TaskHandler {
   private:
    const TaskConstants& constants; /**< Reference to task-related constants. */
    TaskHandle_t gcTaskHandle; /**< Handle for the garbage collection task. */
    int* taskIdHolder; /**< Array to store task IDs. */
    TaskHandle_t** taskHandleHolder; /**< Array to store task handles. */
    Task** taskHolder; /**< Array to store pointers to task objects. */
    int nextTaskId = 100; /**< ID counter for generating unique task IDs. */
    std::atomic<bool> lock{false}; /**< Lock to ensure thread-safe operations. */

    /**
     * @brief Task entry point for initializing tasks.
     * @param taskPointer Pointer to the `Task` object to initialize.
     */
    static void taskInitializer(void* taskPointer);

    /**
     * @brief Garbage collection task to clean up deleted tasks.
     * @param taskHandler Pointer to the `TaskHandler` object managing tasks.
     */
    static void gc(void* taskHandler);

    /**
     * @brief Cleans up task-related resources at a specific index.
     * @param onIndex Index of the task to clean up.
     */
    void clean(const int& onIndex);

   public:
    /**
     * @brief Constructs a `TaskHandler` object.
     * @param constants Reference to the `TaskConstants` for configuration.
     */
    TaskHandler(const TaskConstants& constants);

    /**
     * @brief Creates a new task and adds it to the handler.
     * @param task Pointer to the task to create.
     * @return Unique ID for the created task, or 0 if creation fails.
     */
    int create(Task* task);

    /**
     * @brief Suspends a task by its ID.
     * @param taskId ID of the task to suspend.
     * @return `true` if the task was successfully suspended, `false` otherwise.
     */
    bool suspend(const int& taskId);

    /**
     * @brief Resumes a suspended task by its ID.
     * @param taskId ID of the task to resume.
     * @return `true` if the task was successfully resumed, `false` otherwise.
     */
    bool resume(const int& taskId);

    /**
     * @brief Invokes a task by its ID, resuming or notifying it if needed.
     * @param taskId ID of the task to invoke.
     * @return `true` if the task was successfully invoked, `false` otherwise.
     */
    bool invoke(const int& taskId);

    /**
     * @brief Cancels a task by its ID and cleans up its resources.
     * @param taskId ID of the task to cancel.
     */
    void cancel(const int& taskId);

    /**
     * @brief Retrieves the available stack size of a task.
     * @param taskId ID of the task to query.
     * @return Available stack size in bytes, or 0 if the task is deleted.
     */
    int getAvailableStackSize(const int& taskId);

    /**
     * @brief Sets the priority of a task by its ID.
     * @param taskId ID of the task.
     * @param priority New priority value for the task.
     */
    void setPriority(const int& taskId, int priority);

    /**
     * @brief Retrieves the priority of a task by its ID.
     * @param taskId ID of the task to query.
     * @return Current priority of the task, or the default priority if unavailable.
     */
    int getPriority(const int& taskId);

    /**
     * @brief Retrieves the name of a task by its ID.
     * @param taskId ID of the task to query.
     * @return Name of the task, or an empty string if unavailable.
     */
    const char* getName(const int& taskId);

    /**
     * @brief Retrieves the current state of a task by its ID.
     * @param taskId ID of the task to query.
     * @return Current state of the task, as defined in `TaskConstants`.
     */
    int getState(const int& taskId);

    /**
     * @brief Notifies the garbage collection task to clean up resources.
     */
    void gc();
};

#endif
