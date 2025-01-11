#ifndef LOGGER_H
#define LOGGER_H

#include <ArduinoJson.h>

#include "connector/Connector.h"
#include "util/Constant.h"
#include "util/JsonSchema.h"

class Logger {
   private:
    LogLevel logLevel;
    Connector &connector;
    char buffer[$SYSTEM.SIZE$4K];

   public:
    Logger(Connector &connector);
    void setLogLevel(LogLevel logLevel);
    void log(const LogLevel &level, const char *module, const char *message, const char *details);
};

#endif