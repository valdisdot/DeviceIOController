#ifndef REBOOT_REQUEST_RESOLVER_H
#define REBOOT_REQUEST_RESOLVER_H
#include "request/RequestResolver.h"

class RebootRequestResolver : public RequestResolver {
    public:
    RebootRequestResolver(const char *name);
    int resolve(JsonVariant requestValue) override;
};

#endif