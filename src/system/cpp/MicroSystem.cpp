#include "system/MicroSystem.h"

void copyString(char* destination, const char* source, int limit) {
    if (limit == 0) {
        destination[0] = '\0';
    } else {
        int i = 0;
        limit--;
        while (source[i] != '\0' && i < limit) {
            destination[i] = source[i];
            i++;
        }
        destination[i] = '\0';
    }
}

void concatenateString(char* destination, const char* source, int limit) {
    int destLen = 0;
    while (destLen < limit && destination[destLen] != '\0') destLen++;
    int i = 0;
    while (destLen + i < limit - 1 && source[i] != '\0') {
        destination[destLen + i] = source[i];
        i++;
    }
    if (destLen < limit) destination[destLen + i] = '\0';
}

void convertToASCIIString(char* destination, const byte* byteSource, int limit) {
    int i = 0;
    while (i < limit - 1 && byteSource[i] != '\0') {
        destination[i] = (char)byteSource[i];
        i++;
    }
    if (limit > 0) destination[i] = '\0';
}

int hashCode(const char* string) {
    int hashCode = 0;
    while (*string) {
        hashCode = 31 * hashCode + (unsigned char)(*string);
        string++;
    }
    return hashCode;
}

bool equal(const char* s1, const char* s2) {
    if (hashCode(s1) == hashCode(s2)) {
        while (*s1 && *s2) {
            if (*s1 != *s2) return false;
            s1++;
            s2++;
        }
        if (*s1 == '\0' && *s2 == '\0') return true;
    }
    return false;
}