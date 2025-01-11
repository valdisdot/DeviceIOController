#ifndef SET_MODES_REQUEST_RESOLVER_H
#define SET_MODES_REQUEST_RESOLVER_H
#include "request/RequestResolver.h"
#include "service/PortHandler.h"
#include "service/Storage.h"
#include "controller/MessageExchanger.h"

class SetModesRequestResolver : public RequestResolver {
    PortHandler &portHandler;
    Storage& storage;
    MessageExchanger &messageExchanger;
    public:
    SetModesRequestResolver(const char *name, PortHandler &portHandler, Storage& storage, MessageExchanger &messageExchanger);
    int resolve(JsonVariant requestValue) override;
};

#endif