/**
 * @file TaskConstants.h
 * @brief Defines constants for task types, states, priorities, and handler configurations.
 *
 * This header file contains the `TaskConstants` structure, which provides a centralized
 * collection of constants for managing task behaviors, priorities, and configurations.
 */

#ifndef TASK_CONSTANTS_H
#define TASK_CONSTANTS_H

/**
 * @struct TaskConstants
 * @brief Contains constants for task management and handler configurations.
 *
 * The `TaskConstants` structure defines values for task types, states, priorities, and
 * specific task stack sizes and delays. These constants are used across the system to
 * standardize task configurations and operations.
 */
struct TaskConstants {
    // Task execution types
    const int TASK_TYPE_SINGLE_RUN = 0;           /**< Task type for single execution. */
    const int TASK_TYPE_CYCLIC = 1;               /**< Task type for cyclic execution. */
    const int TASK_TYPE_REACTIVE = 2;             /**< Task type for reactive execution. */

    // Task states
    const int TASK_STATE_UNDEFINED = 0;           /**< Undefined task state. */
    const int TASK_STATE_RUNNING = 1;             /**< Task is currently running. */
    const int TASK_STATE_AWAITS_IN_QUEUE = 2;     /**< Task is waiting in a queue. */
    const int TASK_STATE_AWAINTS_NOTIFICATION = 3;/**< Task is waiting for a notification. */
    const int TASK_STATE_SUSPENDED = 4;           /**< Task is suspended. */
    const int TASK_STATE_DELETED = 5;             /**< Task is deleted. */

    // Task handler configurations
    const int HANDLER_GC_INTERVAL = 60000;        /**< Garbage collection interval for the task handler, in milliseconds. */
    const int HANDLER_HOLDER_SIZE = 30;           /**< Maximum number of tasks held by the handler. */
    const int MAIN_CORE = 0;                      /**< Active core for main task execution. */
    const int BACKGROUND_CORE = 1;                /**< Active core for backgroung task execution. */

    // Task priorities
    const int PRIOTITY_NOW = 32;                  /**< Priority level for immediate execution. */
    const int PRIOTITY_HIGH = 16;                 /**< High priority level. */
    const int PRIOTITY_MIDDLE = 8;                /**< Middle priority level. */
    const int PRIOTITY_LOW = 0;                   /**< Low priority level. */

    // Port handler state collector task configurations
    const int PORT_HANDLER_STATE_COLLECTOR_TASK_STACK_SIZE = 2048; /**< Stack size for state collector task. */
    const int PORT_HANDLER_STATE_COLLECTOR_TASK_PRIORITY = PRIOTITY_HIGH; /**< Priority for state collector task. */

    // Port handler stateful collector task configurations
    const int PORT_HANDLER_STATEFUL_COLLECTOR_TASK_STACK_SIZE = 2048; /**< Stack size for stateful collector task. */
    const int PORT_HANDLER_STATEFUL_COLLECTOR_TASK_DELAY = 10; /**< Delay for stateful collector task, in milliseconds. */
    const int PORT_HANDLER_STATEFUL_COLLECTOR_TASK_PRIORITY = PRIOTITY_NOW; /**< Priority for stateful collector task. */

    // Internal storage task configurations
    const int INTERNAL_STORAGE_TASK_STACK_SIZE = 2048; /**< Stack size for internal storage task. */
    const int INTERNAL_STORAGE_TASK_DELAY = 60000; /**< Delay for internal storage task, in milliseconds. */
    const int INTERNAL_STORAGE_TASK_PRIORITY = PRIOTITY_MIDDLE; /**< Priority for internal storage task. */
};

#endif
