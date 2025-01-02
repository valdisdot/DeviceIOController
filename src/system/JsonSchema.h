#ifndef JSON_SCHEMA_H
#define JSON_SCHEMA_H

struct StateSchema {
    const char* MODES = "modes";
    const char* DATA = "data";
};

struct ControllerStateSchema {
    const char* STATE = "state";
    const char* STATE$WIFI = "wifi";
    const char* STATE$CELLULAR = "cellular";
    const char* STATE$SERIAL = "serial";
    const char* MEMORY = "memory";
    const char* REBOOT_REASON = "reboot_reason";
};

struct NetworkConfigurationSchema {
    const char* MODE = "mode";
    const char* SSID = "ssid";
    const char* PASSWORD = "password";
    const char* APN_NAME = "apn_name";
    const char* APN_USER = "apn_user";
    const char* APN_PASSWORD = "apn_password";
};

struct ServerConfigurationSchema {
    const char* ADDRESS = "address";
    const char* PORT = "port";
    const char* USER = "user";
    const char* PASSWORD = "password";
    const char* CERTIFICATE = "certificate";
};

struct ControllerConfigurationSchema {
    const char* ROOT = "controller";
    const char* LOG_LEVEL = "log_level";
    const char* TRANSMISSION_INTERVAL = "transmission_interval";
};

struct MessageSchema {
    const char* TIMESTAMP = "timestamp";
    const char* ID = "id";
    const char* MESSAGE_ID = "message_id";
    const char* MESSAGE_HASH = "message_hash";
    const char* RESPONSE = "response";
    const char* REQUEST = "request";
    const char* NAME = "name";
    const char* VALUE = "value";
    const char* RESULT = "result";
    const char* TYPE = "type";
    const char* DETAILS = "details";
};

struct LogSchema {
    const char* LEVEL = "level";
    const char* MODULE = "module";
    const char* MESSAGE = "message";
    const char* CAUSE = "cause";
};

const static StateSchema JSON$STATE;
const static ControllerStateSchema JSON$CONTROLLER_STATE;
const static NetworkConfigurationSchema JSON$NETWORK_CONFIGURATION;
const static ServerConfigurationSchema JSON$SERVER_CONFIGURATION;
const static ControllerConfigurationSchema JSON$CONTROLLER_CONFIGURATION;
const static MessageSchema JSON$MESSAGE;
const static LogSchema JSON$LOG;

#endif