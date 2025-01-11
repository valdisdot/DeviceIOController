#ifndef MAKE_BACKUP_REQUEST_RESOLVER_H
#define MAKE_BACKUP_REQUEST_RESOLVER_H
#include "request/RequestResolver.h"
#include "service/Storage.h"

class MakeBackupRequestResolver : public RequestResolver {
    private:
    Storage& storage;
    public:
    MakeBackupRequestResolver(const char *name, Storage& storage);
    int resolve(JsonVariant requestValue) override;
};

#endif