#ifndef JSON_SCHEMA_H
#define JSON_SCHEMA_H

struct BaseSchema {
    const char* ID = "id";
    const char* STATE = "state";
    const char* CONFIGURATION = "configuration";
    const char* CONTROLLER = "controller";

    BaseSchema() = default;
};

struct StateSchema {
    const char* MODES = "modes";
    const char* DATA = "data";
};

struct ConnectionConfigurationSchema {
    const char* ROOT = "network";
    const char* MODE = "mode";
    const char* SSID = "ssid";
    const char* PASSWORD = "password";
    const char* APN_NAME = "apn_name";
    const char* APN_USER = "apn_user";
    const char* APN_PASSWORD = "apn_password";
    const char* TRANSMISSION_INTERVAL = "transmission_interval";

    ConnectionConfigurationSchema() = default;
};

struct ServerConfigurationSchema {
    const char* ROOT = "server";
    const char* ADDRESS = "address";
    const char* PORT = "port";
    const char* USER = "user";
    const char* PASSWORD = "password";
    const char* CERTIFICATE = "certificate";

    ServerConfigurationSchema() = default;
};

struct ControllerStateSchema {
    const char* STATE = "state";
    const char* STATE$WIFI = "wifi";
    const char* STATE$CELLULAR = "cellular";
    const char* STATE$SERIAL = "serial";
    const char* MEMORY = "memory";
    const char* MEMORY$MIN = "min";
    const char* MEMORY$MAX = "max";
    const char* REBOOT_REASON = "reboot_reason";

    ControllerStateSchema() = default;
};

struct MessageSchema {
    const char* MESSAGE_ID = "message_id";     
    const char* MESSAGE_HASH = "message_hash";
    const char* RESPONSE = "response";        
    const char* REQUEST = "request";           
    const char* NAME = "name";                 
    const char* VALUE = "value";              
    const char* RESULT = "result";          
    const char* TYPE = "type";              
    const char* DETAILS = "details";       

    MessageSchema() = default;
};

struct LogSchema {
    const char * TIMESTAMP = "timestamp";
    const char * THEME = "theme";
    const char* INTEGER = "integer";
    const char* TEXT = "text";
    const char* OBJECT = "object";
    const char* LEVEL = "level";
};

#endif