#ifndef PORT_STATE_H
#define PORT_STATE_H

#include "system/MicroSystem.h"

class PortState {
   private:
    JsonDocument holder;
    void eraseModes();
    void eraseData();

   public:
    PortState();
    void copyModesInto(int *destination);
    JsonArrayConst getModesAsJson();
    void setModes(const int *modes);
    void setModes(JsonArrayConst modes);
    void copyDataInto(int *destination);
    JsonArrayConst getDataAsJson();
    void setData(const int *data);
    void setData(JsonArrayConst data);
    void setPortData(const int& port, int data);
    JsonObjectConst getAsJson();

};

#endif