#include "capsule/ControllerConfiguration.h"

LogLevel ControllerConfiguration::getLogLevel() {
    if (holder[JSON$CONTROLLER_CONFIGURATION.LOG_LEVEL].is<unsigned int>()) {
        switch (holder[JSON$CONTROLLER_CONFIGURATION.LOG_LEVEL].as<unsigned int>()) {
            case DEBUG:
                return DEBUG;
            case INFO:
                return INFO;
            case WARNING:
                return WARNING;
            default:
                return $LOG.DEFAULT_LEVEL;
        }
    }
    return $LOG.DEFAULT_LEVEL;
}

int ControllerConfiguration::getTransmissionInterval() {
    return holder[JSON$CONTROLLER_CONFIGURATION.TRANSMISSION_INTERVAL].is<unsigned int>() ? holder[JSON$CONTROLLER_CONFIGURATION.TRANSMISSION_INTERVAL].as<unsigned int>() : $TASK.TASK$PORT_HANDLER$STATE_COLLECTOR$DEFAULT_TRANSMISSION_INTERVAL;
}

JsonObjectConst ControllerConfiguration::getAsJson() {
    return holder.as<JsonObjectConst>();
}

void ControllerConfiguration::updateFromJson(JsonObjectConst configuration) {
    if (configuration) {
        if (configuration[JSON$CONTROLLER_CONFIGURATION.LOG_LEVEL].is<unsigned int>()) holder[JSON$CONTROLLER_CONFIGURATION.LOG_LEVEL] = configuration[JSON$CONTROLLER_CONFIGURATION.LOG_LEVEL];
        if (configuration[JSON$CONTROLLER_CONFIGURATION.TRANSMISSION_INTERVAL].is<unsigned int>()) holder[JSON$CONTROLLER_CONFIGURATION.TRANSMISSION_INTERVAL] = configuration[JSON$CONTROLLER_CONFIGURATION.TRANSMISSION_INTERVAL];
    }
}
