/**
 * @file Task.h
 * @brief Defines an abstract base class for tasks with configurable execution properties.
 *
 * This header file declares the `Task` class, providing a framework for defining tasks
 * with various execution types, priorities, and delays. Derived classes must implement
 * the `execute` method to define specific task behavior.
 */

#ifndef TASK_H
#define TASK_H

#include "TaskConstants.h"

/**
 * @class Task
 * @brief Abstract base class for defining tasks with configurable execution properties.
 *
 * The `Task` class encapsulates properties and behaviors for tasks, such as execution type,
 * delay, priority, and stack size. Derived classes must implement the `execute` method to
 * specify task functionality.
 */
class Task {
   protected:
    const char* name;                             /**< Name of the task. */
    const int startupDelay;                       /**< Delay before the task starts executing, in milliseconds. */
    const int loopDelay;                          /**< Delay between task executions in cyclic mode, in milliseconds. */
    const int executionType;                      /**< Type of task execution (cyclic, reactive, or single run). */
    const int stackSize;                          /**< Stack size allocated for the task. */
    const int priority;                           /**< Priority level of the task. */
    const TaskConstants& constants;               /**< Reference to a TaskConstants object for shared constants. */

   public:
    /**
     * @brief Constructs a Task object.
     * @param name Name of the task.
     * @param startupDelay Delay before the task starts executing, in milliseconds.
     * @param loopDelay Delay between task executions in cyclic mode, in milliseconds.
     * @param executionType Type of task execution (cyclic, reactive, or single run).
     * @param stackSize Stack size allocated for the task.
     * @param priority Priority level of the task.
     * @param constants Reference to a TaskConstants object for shared constants.
     */
    Task(const char* name, int startupDelay, int loopDelay, int executionType, int stackSize, int priority, const TaskConstants& constants);

    /**
     * @brief Retrieves the name of the task.
     * @return Pointer to the name of the task.
     */
    const char* getName();

    /**
     * @brief Retrieves the startup delay of the task.
     * @return Reference to the startup delay in milliseconds.
     */
    const int& getStartupDelay();

    /**
     * @brief Retrieves the loop delay of the task.
     * @return Reference to the loop delay in milliseconds.
     */
    const int& getLoopDelay();

    /**
     * @brief Checks if the task is cyclic.
     * @return `true` if the task has cyclic execution, `false` otherwise.
     */
    bool isCyclic();

    /**
     * @brief Checks if the task is reactive.
     * @return `true` if the task has reactive execution, `false` otherwise.
     */
    bool isReactive();

    /**
     * @brief Checks if the task is a single-run task.
     * @return `true` if the task executes only once, `false` otherwise.
     */
    bool isSingleRun();

    /**
     * @brief Retrieves the stack size of the task.
     * @return Reference to the stack size allocated for the task.
     */
    const int& getStackSize();

    /**
     * @brief Retrieves the priority level of the task.
     * @return Reference to the priority level of the task.
     */
    const int& getPriority();

    /**
     * @brief Abstract method for executing the task.
     *
     * Derived classes must implement this method to define task-specific behavior.
     */
    virtual void execute() = 0;
};

#endif
