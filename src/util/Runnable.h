#ifndef RUNNABLE_H
#define RUNNABLE_H

class Runnable {
    public:
        virtual void init() = 0;
        virtual void run() = 0;
};

#endif