/**
 * @file ControllerConstants.h
 * @brief Contains logic constants for the controller.
 *
 * This header file defines a `ControllerConstants` structure that centralizes
 * constants used in the controller's logic, including port modes and limits.
 */

#ifndef CONTROLLER_CONSTANTS_H
#define CONTROLLER_CONSTANTS_H

/**
 * @struct ControllerConstants
 * @brief Structure containing constants for controller logic.
 *
 * This structure provides integer constants that represent the last available port,
 * port modes, and various other logical values used in the controller.
 */
struct ControllerConstants {
    const int LAST_PORT = 38;                            /**< The last available port number to use. */
    const int NOT_INITIALIZED = 0;                      /**< Represents an uninitialized port. */
    const int MODE_LOGICAL_INPUT = 1;                   /**< Represents a logical input mode. */
    const int MODE_LOGICAL_OUTPUT = 2;                  /**< Represents a logical output mode. */
    const int MODE_VALUE_INPUT = 3;                     /**< Represents a value input mode. */
    const int MODE_VALUE_OUTPUT = 4;                    /**< Represents a value output mode. */
    const int MODE_INVERSED_LOGICAL_INPUT = 5;          /**< Represents an inversed logical input mode. */
    const int MODE_STATEFUL_LOGICAL_INPUT = 6;          /**< Represents a stateful logical input mode. */

    const int CLIENT_SERIAL = 0;
    const int CLIENT_MQTT = 1;
    const int CLIENT_HTTP = 2;
};

#endif
