#ifndef MICRO_SYSTEM_H
#define MICRO_SYSTEM_H

#include <Arduino.h>
#include <ArduinoJson.h>

#include "system/Constant.h"
#include "system/JsonSchema.h"

/**
 * @brief Copies a string to the destination, overriding its contents.
 *
 * @param destination The destination buffer.
 * @param source The source string to copy.
 * @param limit The maximum number of characters to copy.
 */
void copyString(char* destination, const char* source, int limit);

/**
 * @brief Appends a source string to the destination string.
 *
 * @param destination The destination buffer.
 * @param source The source string to append.
 * @param limit The maximum number of characters to append.
 */
void concatenateString(char* destination, const char* source, int limit);

/**
 * @brief Converts a byte array into a null-terminated ASCII string.
 *
 * @param destination The destination buffer for the ASCII string.
 * @param byteSource The source byte array.
 * @param limit The maximum number of bytes to convert.
 */
void convertToASCIIString(char* destination, const byte* byteSource, int limit);

/**
 * @brief Checks if a string is empty.
 *
 * @param s The string to check.
 * @return true if the string is empty; otherwise false.
 */
bool isEmpty(const char* s);

/**
 * @brief Checks if a string contains at least one non-whitespace character.
 *
 * @param s The string to check.
 * @return true if the string is blank; otherwise false.
 */
bool isBlank(const char* s);

/**
 * @brief Calculates the hash code of a string.
 *
 * @param string The input string.
 * @return The hash code as an integer.
 */
int hashCode(const char* string);

/**
 * @brief Compares two strings for equality.
 *
 * @param s1 The first string.
 * @param s2 The second string.
 * @return true if the strings are equal; otherwise false.
 */
bool equal(const char* s1, const char* s2);

#endif
