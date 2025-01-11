#include "controller/Logger.h"

Logger::Logger(Connector& connector) : connector(connector) {
}

void Logger::setLogLevel(LogLevel logLevel) {
    this->logLevel = logLevel;
}

void Logger::log(const LogLevel& level, const char* module, const char* message, const char* details) {
    unsigned long timestamp = millis();
    if (level >= logLevel && (module || message || details)) {
        JsonDocument log;
        const char* _level;
        switch (level) {
            case DEBUG:
                _level = $LOG.DEBUG$STRING;
                break;
            case INFO:
                _level = $LOG.INFO$STRING;
                break;
            case WARNING:
                _level = $LOG.WARNING$STRING;
                break;
            case ERROR:
                _level = $LOG.ERROR$STRING;
                break;
            default:
                break;
        }
        log[JSON$MESSAGE.TIMESTAMP] = timestamp;
        log[JSON$LOG.LEVEL] = _level;
        if (module) log[JSON$LOG.MODULE] = module;
        if (message) log[JSON$LOG.MESSAGE] = message;
        if (details) log[JSON$LOG.CAUSE] = details;
        serializeJsonPretty(log, buffer);
        connector.sendLog(buffer);
    }
}