#ifndef MICRO_SYSTEM_H
#define MICRO_SYSTEM_H

#include <ArduinoJson.h>
#include <Arduino.h>
#include "system/JsonSchema.h"
#include "system/Constant.h"

void copyString(char *destination, const char *source, int limit);
void concatenateString(char* destination, const char* source, int limit);
void convertToASCIIString(char* destination, const byte* byteSource, int limit);
bool isEmpty(const char* s);
bool isBlank(const char* s);
int hashCode(const char *string);
bool equal(const char *s1, const char *s2);

#endif