#ifndef SYSTEM_CONSTANT_H
#define SYSTEM_CONSTANT_H

/**
 * @brief System-wide constants.
 */
struct SystemConstant {
    /// Array size of 32.
    const static int SIZE$32 = 32;
    /// Array size of 64.
    const static int SIZE$64 = 64;
    /// Array size of 1024.
    const static int SIZE$1K = 1024;
    /// Array size of 2048.
    const static int SIZE$2K = 2048;
    /// Array size of 4096.
    const static int SIZE$4K = 4096;
    /// Default integer no-value.
    const int NO_VALUE$INT = -1;
    /// Default string no-value.
    const char* NO_VALUE$STR = "";
};

/**
 * @brief Port-specific constants.
 */
struct PortConstant {
    /// Number of ports available for iteration.
    const int COUNT = 40;
    /// Mode for uninitialized ports.
    const int MODE$NOT_INITIALIZED = 0;
    /// Mode for logical input.
    const int MODE$LOGICAL_INPUT = 1;
    /// Mode for logical output.
    const int MODE$LOGICAL_OUTPUT = 2;
    /// Mode for value input.
    const int MODE$VALUE_INPUT = 3;
    /// Mode for value output.
    const int MODE$VALUE_OUTPUT = 4;
    /// Mode for inversed logical input.
    const int MODE$INVERSED_LOGICAL_INPUT = 5;
    /// Mode for stateful logical input.
    const int MODE$STATEFUL_LOGICAL_INPUT = 6;
    /// Mode for initialization forbidden.
    const int MODE$INIT_FORBIDDEN = 10;
};

/**
 * @brief Constants for non-volatile storage keys/names.
 */
struct InternalStorageConstant {
    /// Configuration key.
    const char* CONFIGURATION = "configuration";
    /// Network configuration key.
    const char* CONFIGURATION$NETWORK = "network";
    /// Server configuration key.
    const char* CONFIGURATION$SERVER = "server";
    /// Controller configuration key.
    const char* CONFIGURATION$CONTROLLER = "controller";
    /// State key.
    const char* STATE = "state";
    /// Modes state key.
    const char* STATE$MODES = "modes";
    /// Data state key.
    const char* STATE$DATA = "data";
};

/**
 * @brief Constants related to tasks and task handlers.
 */
struct TaskConstant {
    /// Execution type for single-run tasks.
    const int TYPE$SINGLE_RUN = 0;
    /// Execution type for cyclic tasks.
    const int TYPE$CYCLIC = 1;
    /// Execution type for reactive tasks.
    const int TYPE$REACTIVE = 2;

    /// Undefined task state.
    const int STATE$UNDEFINED = 0;
    /// Running task state.
    const int STATE$RUNNING = 1;
    /// Task awaiting in queue.
    const int STATE$AWAITS_IN_QUEUE = 2;
    /// Task awaiting notification.
    const int STATE$AWAITS_NOTIFICATION = 3;
    /// Suspended task state.
    const int STATE$SUSPENDED = 4;
    /// Deleted task state.
    const int STATE$DELETED = 5;

    /// High-priority task.
    const int PRIOTITY$NOW = 32;
    /// Medium-priority task.
    const int PRIOTITY$HIGH = 16;
    /// Low-priority task.
    const int PRIOTITY$MIDDLE = 8;
    /// Lowest-priority task.
    const int PRIOTITY$LOW = 0;

    /// Garbage collector interval for completed tasks.
    const int HANDLER$GC_INTERVAL = 60000;
    /// Maximum number of tasks in the handler.
    const int HANDLER$HOLDER_SIZE = 30;

    /// Main core identifier.
    const int CORE$MAIN = 0;
    /// Background core identifier.
    const int CORE$BACKGROUND = 1;

    /// Default transmission interval for port handler state collector task.
    const int TASK$PORT_HANDLER$STATE_COLLECTOR$DEFAULT_TRANSMISSION_INTERVAL = 1000;

    /// Stack size for stateful port data collector task.
    const int TASK$PORT_HANDLER$STATEFUL_COLLECTOR$STACK_SIZE = 8192;
    /// Delay for stateful port data collector task.
    const int TASK$PORT_HANDLER$STATEFUL_COLLECTOR$DELAY = 10;
    /// Priority for stateful port data collector task.
    const int TASK$PORT_HANDLER$STATEFUL_COLLECTOR$PRIORITY = PRIOTITY$NOW;

    /// Stack size for storage backup task.
    const int TASK$STORAGE_BACKUP$STACK_SIZE = 8192;
    /// Delay for storage backup task.
    const int TASK$STORAGE_BACKUP$DELAY = 10000;
    /// Priority for storage backup task.
    const int TASK$STORAGE_BACKUP$PRIORITY = PRIOTITY$MIDDLE;

    /// Stack size for free memory collector task.
    const int TASK$MEMORY_COLLECTOR$STACK_SIZE = 8192;
    /// Delay for free memory collector task.
    const int TASK$MEMORY_COLLECTOR$DELAY = 60000; //ones per minute
    /// Priority for free memory collector task.
    const int TASK$MEMORY_COLLECTOR$PRIORITY = PRIOTITY$HIGH;

    /// Stack size for free memory collector task.
    const int TASK$SIGNAL_STRENGTH_COLLECTOR$STACK_SIZE = 8192;
    /// Delay for free memory collector task.
    const int TASK$SIGNAL_STRENGTH_COLLECTOR$DELAY = 60000; //ones per minute
    /// Priority for free memory collector task.
    const int TASK$SIGNAL_STRENGTH_COLLECTOR$PRIORITY = PRIOTITY$HIGH;

    /// Stack size for client runner task.
    const int TASK$CLIENT_RUNNER$STACK_SIZE = 16384;
    /// Delay for client runner task.
    const int TASK$CLIENT_RUNNER$DELAY = 100;
    /// Priority for client runner task.
    const int TASK$CLIENT_RUNNER$PRIORITY = PRIOTITY$NOW;
};

/**
 * @brief Messaging-specific constants.
 */
struct MessageConstant {
    /// Response code for success.
    const int RESPONSE$OK = 1;
    /// Response code for failure.
    const int RESPONSE$FAIL = 0;
    /// Response code for undefined state.
    const int RESPONSE$UNDEFINED = -1;
    /// Request to set modes.
    const char* REQUEST$SET_MODES = "set_modes";
    /// Request to set data.
    const char* REQUEST$SET_DATA = "set_data";
    /// Request to configure the network.
    const char* REQUEST$CONFIGURE_NETWORK = "configure_network";
    /// Request to configure the server.
    const char* REQUEST$CONFIGURE_SERVER = "configure_server";
    /// Request to configure the controller.
    const char* REQUEST$CONFIGURE_CONTROLLER = "configure_controller";
    /// Request to reboot.
    const char* REQUEST$REBOOT = "reboot";
    /// Request to send controller state.
    const char* REQUEST$SEND_CONTROLLER_STATE = "send_controller_state";
    /// Request to send state (data from the ports).
    const char* REQUEST$SEND_STATE = "send_state";
    /// Request to make a backup.
    const char* REQUEST$MAKE_BACKUP = "make_backup";
};

/**
 * @brief MQTT topic-specific constants.
 */
struct MqttConstant {
    /// MQTT topic part: "to".
    const char* TOPIC$TO = "to";
    /// MQTT topic part: "from".
    const char* TOPIC$FROM = "from";
    /// MQTT topic part: "state".
    const char* TOPIC$STATE = "state";
    /// MQTT topic part: "controller".
    const char* TOPIC$CONTROLLER = "controller";
    /// MQTT topic part: "request".
    const char* TOPIC$REQUEST = "request";
    /// MQTT topic part: "response".
    const char* TOPIC$RESPONSE = "response";
    /// MQTT topic part: "log".
    const char* TOPIC$LOG = "log";
};

/**
 * @brief Network connection constants.
 */
struct NetworkConstant {
    /// Serial connection mode.
    const int MODE$SERIAL = 1;
    /// Wi-Fi connection mode.
    const int MODE$WIFI = 2;
    /// Cellular connection mode.
    const int MODE$CELLULAR = 3;
    /// Keep-alive duration (seconds).
    const int KEEP_ALIVE = 90;
    /// Connection attempts for internet connections.
    const int CONNECTION_ATTEMPTS = 5;
    /// Baud rate for serial connection.
    const int SERIAL$BAUD_RATE = 38400;
};

/**
 * @brief Logging levels.
 */
enum LogLevel {
    DEBUG = 0,    ///< Debug level.
    INFO = 1,     ///< Info level.
    WARNING = 2,  ///< Warning level.
    ERROR = 100   ///< Error level.
};

/**
 * @brief Logging-specific constants.
 */
struct LogConstant {
    /// Debug level string representation.
    const char* DEBUG$STRING = "DEBUG";
    /// Info level string representation.
    const char* INFO$STRING = "INFO";
    /// Warning level string representation.
    const char* WARNING$STRING = "WARNING";
    /// Error level string representation.
    const char* ERROR$STRING = "ERROR";
    /// Default log level for the system.
    const LogLevel DEFAULT_LEVEL = ERROR;
};

/**
 * @brief Initialization constants (vaults).
 */
const static SystemConstant $SYSTEM;                     ///< System-wide constants.
const static PortConstant $PORT;                         ///< Port-specific constants.
const static InternalStorageConstant $INTERNAL_STORAGE;  ///< Internal storage constants.
const static TaskConstant $TASK;                         ///< Task-specific constants.
const static MessageConstant $MESSAGE;                   ///< Message-specific constants.
const static MqttConstant $MQTT;                         ///< MQTT-specific constants.
const static NetworkConstant $NETWORK;                   ///< Network-specific constants.
const static LogConstant $LOG;                           ///< Logging-specific constants.

#endif
