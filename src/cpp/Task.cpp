#include "Task.h"

Task::Task(const char* name, int startupDelay, int loopDelay, int executionType, int stackSize, int priority, const TaskConstants& constants)
    : name(name), startupDelay(startupDelay), loopDelay(loopDelay), executionType(executionType), stackSize(stackSize), priority(priority), constants(constants) {}

const char* Task::getName() {
    return name;
}

const int& Task::getStartupDelay() {
    return startupDelay;
}

const int& Task::getLoopDelay() {
    return loopDelay;
}

bool Task::isCyclic() {
    return executionType == constants.TASK_TYPE_CYCLIC;
}

bool Task::isReactive() {
    return executionType == constants.TASK_TYPE_REACTIVE;
}

bool Task::isSingleRun() {
    return executionType == constants.TASK_TYPE_SINGLE_RUN;
}

const int& Task::getStackSize() {
    return stackSize;
}

const int& Task::getPriority() {
    return priority;
}