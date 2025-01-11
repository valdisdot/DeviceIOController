#define VERSION = 1.1

#include "util/Runnable.h"
#include "controller/Boot.h"

Runnable *runnable = new Boot();

void setup() {
    runnable->init();
}

void loop() {
    runnable->run();
}


