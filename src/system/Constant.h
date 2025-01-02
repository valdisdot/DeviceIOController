#ifndef SYSTEM_CONSTANT_H
#define SYSTEM_CONSTANT_H

struct SystemConstant {
    const static int SIZE$16 = 16;
    const static int SIZE$32 = 32;
    const static int SIZE$64 = 64;
    const static int SIZE$128 = 128;
    const static int SIZE$512 = 512;
    const static int SIZE$1K = 1024;
    const static int SIZE$2K = 2048;
    const static int SIZE$4K = 4096;
    const static int SIZE$8K = 8192;

    const int NO_VALUE$INT = -1;
    const char* NO_VALUE$STR = "";
    const char* NULL_STR = "null";
};

struct PortConstant {
    const int COUNT = 40;
    const int MODE$NOT_INITIALIZED = 0;
    const int MODE$LOGICAL_INPUT = 1;
    const int MODE$LOGICAL_OUTPUT = 2;
    const int MODE$VALUE_INPUT = 3;
    const int MODE$VALUE_OUTPUT = 4;
    const int MODE$INVERSED_LOGICAL_INPUT = 5;
    const int MODE$STATEFUL_LOGICAL_INPUT = 6;
    const int MODE$INIT_FORBIDDEN = 10;
};

struct InternalStorageConstant {
    const char* CONFIGURATION = "configuration";
    const char* CONFIGURATION$NETWORK = "network";
    const char* CONFIGURATION$SERVER = "server";
    const char* CONFIGURATION$CONTROLLER = "controller";
    const char* STATE = "state";
    const char* STATE$MODES = "modes";
    const char* STATE$DATA = "data";
};

struct TaskConstant {
    const int TYPE$SINGLE_RUN = 0;
    const int TYPE$CYCLIC = 1;
    const int TYPE$REACTIVE = 2;

    const int STATE$UNDEFINED = 0;
    const int STATE$RUNNING = 1;
    const int STATE$AWAITS_IN_QUEUE = 2;
    const int STATE$AWAINTS_NOTIFICATION = 3;
    const int STATE$SUSPENDED = 4;
    const int STATE$DELETED = 5;

    const int PRIOTITY$NOW = 32;
    const int PRIOTITY$HIGH = 16;
    const int PRIOTITY$MIDDLE = 8;
    const int PRIOTITY$LOW = 0;

    const int HANDLER$GC_INTERVAL = 60000;
    const int HANDLER$HOLDER_SIZE = 30;

    const int CORE$MAIN = 0;
    const int CORE$BACKGROUND = 1;

    const int TASK$PORT_HANDLER$STATE_COLLECTOR$STACK_SIZE = 4048;
    const int TASK$PORT_HANDLER$STATE_COLLECTOR$DEFAULT_TRANSMISSION_INTERVAL = 1000;
    const int TASK$PORT_HANDLER$STATE_COLLECTOR$PRIORITY = PRIOTITY$HIGH;

    const int TASK$PORT_HANDLER$STATEFUL_COLLECTOR$STACK_SIZE = 4048;
    const int TASK$PORT_HANDLER$STATEFUL_COLLECTOR$DELAY = 10;
    const int TASK$PORT_HANDLER$STATEFUL_COLLECTOR$PRIORITY = PRIOTITY$NOW;

    const int TASK$INTERNAL_STORAGE$STACK_SIZE = 8192;
    const int TASK$INTERNAL_STORAGE$DELAY = 2000;  // 1 minute 60000
    const int TASK$INTERNAL_STORAGE$PRIORITY = PRIOTITY$MIDDLE;

    const int TASK$CLIENT_RUNNER$STACK_SIZE = 16384;
    const int TASK$CLIENT_RUNNER$DELAY = 100;
    const int TASK$CLIENT_RUNNER$PRIORITY = PRIOTITY$NOW;
};

struct MessageConstant {
    const int RESPONSE$OK = 1;
    const int RESPONSE$FAIL = 0;
    const int RESPONSE$UNDEFINED = -1;

    const char* REQUEST$SET_MODES = "set_modes";
    const char* REQUEST$SET_DATA = "set_data";
    const char* REQUEST$CONFIGURE_NETWORK = "configure_network";
    const char* REQUEST$CONFIGURE_SERVER = "configure_server";
    const char* REQUEST$CONFIGURE_CONTROLLER = "configure_controller";
    const char* REQUEST$REBOOT = "reboot";
    const char* REQUEST$SEND_CONTROLLER_STATE = "send_controller_state";
    const char* REQUEST$MAKE_BACKUP = "make_backup";
};

struct MqttConstant {
    const char* TOPIC$TO = "to";
    const char* TOPIC$FROM = "from";
    const char* TOPIC$STATE = "state";
    const char* TOPIC$CONTROLLER = "controller";
    const char* TOPIC$REQUEST = "request";
    const char* TOPIC$RESPONSE = "response";
    const char* TOPIC$LOG = "log";
};

struct NetworkConstant {
    const int KEEP_ALIVE = 90;
    const int CONNECTION_ATTEMPTS = 5;
    const int MODE$SERIAL = 1;
    const int MODE$WIFI = 2;
    const int MODE$CELLULAR = 3;
    const int SERIAL$BAUD_RATE = 38400;
};

enum LogLevel {
    DEBUG = 0,
    INFO = 1,
    WARNING = 2,
    ERROR = 100
};

struct LogConstant {
    const char* DEBUG$STRING = "DEBUG";
    const char* INFO$STRING = "INFO";
    const char* WARNING$STRING = "WARNING";
    const char* ERROR$STRING = "ERROR";

    const LogLevel DEFAULT_LEVEL = ERROR;
};

const static SystemConstant $SYSTEM;
const static PortConstant $PORT;
const static InternalStorageConstant $INTERNAL_STORAGE;
const static TaskConstant $TASK;
const static MessageConstant $MESSAGE;
const static MqttConstant $MQTT;
const static NetworkConstant $NETWORK;
const static LogConstant $LOG;

#endif