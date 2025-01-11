#ifndef SEND_STATE_REQUEST_RESOLVER_H
#define SEND_STATE_REQUEST_RESOLVER_H
#include "request/RequestResolver.h"
#include "controller/MessageExchanger.h"

class SendStateRequestResolver : public RequestResolver {
    private:
    MessageExchanger &messageExchanger;
    public:
    SendStateRequestResolver(const char *name, MessageExchanger &messageExchanger);
    int resolve(JsonVariant requestValue) override;
};

#endif