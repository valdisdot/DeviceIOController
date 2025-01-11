#ifndef JSON_SCHEMA_H
#define JSON_SCHEMA_H

/**
 * @brief Schema for state-related JSON fields.
 */
struct StateSchema {
    /// Key for modes.
    const char* MODES = "modes";
    /// Key for data.
    const char* DATA = "data";
};

/**
 * @brief Schema for controller state JSON fields.
 */
struct ControllerStateSchema {
    /// Key for state.
    const char* MODE = "mode";
    /// Key for signal strenght.
    const char* SIGNAL_STRENGTH = "signal_strength";
    /// Key for memory size.
    const char* MEMORY = "memory";
    /// Key for reboot reason.
    const char* REBOOT_REASON = "reboot_reason";
};

/**
 * @brief Schema for network configuration JSON fields.
 */
struct NetworkConfigurationSchema {
    /// Key for connection mode.
    const char* MODE = "mode";
    /// Key for Wi-Fi SSID.
    const char* SSID = "ssid";
    /// Key for Wi-Fi password.
    const char* PASSWORD = "password";
    /// Key for APN name.
    const char* APN_NAME = "apn_name";
    /// Key for APN username.
    const char* APN_USER = "apn_user";
    /// Key for APN password.
    const char* APN_PASSWORD = "apn_password";
};

/**
 * @brief Schema for server configuration JSON fields.
 */
struct ServerConfigurationSchema {
    /// Key for server address.
    const char* ADDRESS = "address";
    /// Key for server port.
    const char* PORT = "port";
    /// Key for server user.
    const char* USER = "user";
    /// Key for server password.
    const char* PASSWORD = "password";
    /// Key for server certificate.
    const char* CERTIFICATE = "certificate";
};

/**
 * @brief Schema for controller configuration JSON fields.
 */
struct ControllerConfigurationSchema {
    /// Key for log level.
    const char* LOG_LEVEL = "log_level";
    /// Key for transmission interval.
    const char* TRANSMISSION_INTERVAL = "transmission_interval";
};

/**
 * @brief Schema for message-related JSON fields.
 */
struct MessageSchema {
    /// Key for timestamp.
    const char* TIMESTAMP = "timestamp";
    /// Key for message ID.
    const char* MESSAGE_ID = "message_id";
    /// Key for request.
    const char* REQUEST = "request";
    /// Key for name.
    const char* NAME = "name";
    /// Key for value.
    const char* VALUE = "value";
    /// Key for response.
    const char* RESPONSE = "response";
    /// Key for result.
    const char* RESULT = "result";
};

/**
 * @brief Schema for log-related JSON fields.
 */
struct LogSchema {
    /// Key for log level.
    const char* LEVEL = "level";
    /// Key for module name.
    const char* MODULE = "module";
    /// Key for log message.
    const char* MESSAGE = "message";
    /// Key for cause of the log entry.
    const char* CAUSE = "cause";
};

/**
 * @brief JSON schema instances for various purposes.
 */

const static StateSchema JSON$STATE;                                       ///< State-related JSON schema.
const static ControllerStateSchema JSON$CONTROLLER_STATE;                  ///< Controller state JSON schema.
const static NetworkConfigurationSchema JSON$NETWORK_CONFIGURATION;        ///< Network configuration JSON schema.
const static ServerConfigurationSchema JSON$SERVER_CONFIGURATION;          ///< Server configuration JSON schema.
const static ControllerConfigurationSchema JSON$CONTROLLER_CONFIGURATION;  ///< Controller configuration JSON schema.
const static MessageSchema JSON$MESSAGE;                                   ///< Message-related JSON schema.
const static LogSchema JSON$LOG;                                           ///< Log-related JSON schema.

#endif
