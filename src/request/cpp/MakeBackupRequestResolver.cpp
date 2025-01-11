#include "request/MakeBackupRequestResolver.h"

MakeBackupRequestResolver::MakeBackupRequestResolver(const char* name, Storage& storage) : RequestResolver(name, false), storage(storage) {}

int MakeBackupRequestResolver::resolve(JsonVariant requestValue) {
    storage.backupConfiguration();
    storage.backupState();
    return $MESSAGE.RESPONSE$OK;
}
