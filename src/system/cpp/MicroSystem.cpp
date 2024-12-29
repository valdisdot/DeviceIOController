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