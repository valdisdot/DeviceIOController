#ifndef PORT_STATE_H
#define PORT_STATE_H

#include "util/Constant.h"
#include "util/JsonSchema.h"
#include "util/Function.h"
#include <ArduinoJson.h>

class PortState {
   private:
    JsonDocument holder;

   public:
    PortState();
    void copyModesInto(int *destination);
    JsonArrayConst getModesAsJson();
    void setModes(const int *modes);
    void setModes(JsonArrayConst modes);
    void setPortMode(const int& port, int mode);
    void copyDataInto(int *destination);
    JsonArrayConst getDataAsJson();
    void setData(const int *data);
    void setData(JsonArrayConst data);
    void setPortData(const int& port, int data);
    JsonObjectConst getAsJson();

};

#endif