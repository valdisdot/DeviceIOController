#ifndef MICRO_SYSTEM_H
#define MICRO_SYSTEM_H

#include <ArduinoJson.h>
#include <Arduino.h>
#include "system/JsonSchema.h"
#include "system/Constant.h"

const static bool DEBUG_MODE = true;

const static SystemConstant CONSTANT;
const static TaskConstant TASK_CONSTANT;
const static BaseSchema SCHEMA_BASE;
const static StateSchema SCHEMA_STATE;
const static ConnectionConfigurationSchema SCHEMA_CONNECTION_CONFIGURATION;
const static ServerConfigurationSchema SCHEMA_SERVER_CONFIGURATION;
const static ControllerStateSchema SCHEMA_CONTROLLER_STATE;
const static RequestType REQUEST_TYPE;
const static MessageSchema SCHEMA_MESSAGE;

void copyString(char *destination, const char *source, int limit);
int hashCode(const char *string);
bool equal(const char *s1, const char *s2);

#endif